/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 13:33:03 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/25 15:59:46 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "job_control.h"

void		jc_garbage_collector(t_jc *jc)
{
	t_list		*proc_list;
	t_list		*job_list;
	t_jc_job	*job;
	t_jc_proc	*proc;
	int			should_delete;

	job_list = jc->job_list;
	while (job_list)
	{
		job = (t_jc_job*)job_list->content;
		proc_list = job->proc_list;
		should_delete = 1;
		while (proc_list)
		{
			proc = (t_jc_proc*)proc_list->content;
			if (proc->status != DONE && proc->status != KILLED)
				should_delete = 0;
			proc_list = proc_list->next;
		}
		if (job != jc->fg_job && should_delete)
			bi_jobs(1, NULL, NULL, NULL);
		job_list = job_list->next;
		if (should_delete)
			jc_delete_tag(job->tag);
	}
}

void		jc_set_job_as_running(t_jc_job *job)
{
	t_list		*proc_list;
	t_jc_proc	*proc;

	proc_list = job->proc_list;
	while (proc_list)
	{
		proc = (t_jc_proc*)proc_list->content;
		proc_list = proc_list->next;
		proc->status = RUNNING;
	}
}

void		jc_update_job(t_jc_job *job)
{
	t_list		*proc_list;
	t_jc_proc	*proc;
	int			wait_res;
	int			status;

	proc_list = job->proc_list;
	if (!job)
		return ;
	if (!job->proc_list)
	{
		jc_delete_tag(job->tag);
		return ;
	}
	while (proc_list)
	{
		proc = (t_jc_proc*)proc_list->content;
		proc_list = proc_list->next;
		if (proc->status == DONE || proc->status == KILLED ||
			(wait_res = waitpid(proc->pid, &status, WUNTRACED
				| WNOHANG) == 0))
			continue ;
		jc_update_proc(proc, status);
	}
}

void		jc_update_all(void)
{
	t_list		*job_list;
	t_jc_job	*job;

	job_list = jc_get()->job_list;
	while (job_list)
	{
		job = ((t_jc_job*)job_list->content);
		job_list = job_list->next;
		jc_update_job(job);
	}
	jc_garbage_collector(jc_get());
}

void		jc_update_proc(t_jc_proc *proc, int status)
{
	if (WIFEXITED(status) && ((proc->status = DONE) || 1))
		proc->rvalue = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && ((proc->status = KILLED) || 1))
		proc->rvalue = WTERMSIG(status);
	else if (WIFSTOPPED(status) && ((proc->status = SUSPENDED) || 1))
		proc->rvalue = WSTOPSIG(status);
	else
		proc->status = RUNNING;
	if (proc->status == KILLED && proc->rvalue == 2)
		kill(getpid(), SIGINT);
}
