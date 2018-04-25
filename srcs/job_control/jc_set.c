/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 13:13:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/25 09:38:29 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <signal.h>
#include "sh21.h"

static void	jc_change_pgrp(t_jc_job *job, int mode)
{
	int kill_res;
	t_list *proc_list;
	t_jc_proc *proc;

	proc_list = job->pid_list;
	if (mode == BG)
	{
		if (tcsetpgrp(STDIN_FILENO, getpgrp()))
			ft_exit(errno, "tcsetpgrp");
		while (proc_list)
		{
			proc = (t_jc_proc*)proc_list->content;
			if (proc->status == SUSPENDED)
			{
				kill_res = kill(proc->pid, SIGCONT);
				if (kill_res != 0)
					ft_exit(errno, "killpg");
			}
			proc_list = proc_list->next;
		}
		ft_printf("[%d] %d (%C)\n", job->tag, job->pgid, 8675);
		return ;
	}
	while (proc_list)
	{
		proc = (t_jc_proc*)proc_list->content;
		if (proc->status == SUSPENDED)
		{
			kill_res = kill(proc->pid, SIGCONT);
			if (kill_res != 0)
				ft_exit(errno, "killpg");
		}
		jc_get()->fg_job = job;
		if (tcsetpgrp(STDIN_FILENO, job->pgid))
			ft_exit(errno, "tcsetpgrp");
		proc_list = proc_list->next;
	}

}

static int	jc_wait(t_jc_job *job, int mode)
{
	int status;
	int wait_res;
	t_list	*proc_list;

	status = 0;
	if (mode == BG)
		jc_update_job(job);
	else
	{
		proc_list = job->pid_list;
		while (proc_list)
		{
			wait_res = waitpid(((t_jc_proc*)proc_list->content)->pid,
				&status, WUNTRACED);
			if (wait_res < 0 && errno != ECHILD)
				ft_exit(errno, "waitpid");
			else if (wait_res < 0 && errno == ECHILD)
				break ;
			jc_update_proc(((t_jc_proc*)proc_list->content), status);
			proc_list = proc_list->next;
		}
		tcsetpgrp(0, getpgrp());
	}
	return (status);
}

int			jc_set(t_jc_tag tag, int mode)
{
	t_list		*jb_list;
	t_jc_job*	job;
	int			res;

	jb_list = jc_get()->job_list;
	while (jb_list)
	{
		job = ((t_jc_job*)jb_list->content);
		if (job->tag == tag)
		{
			jc_change_pgrp(job, mode);
			res = jc_wait(job, mode);
			return (res);
		}
		jb_list = jb_list->next;
	}
	return (0);
}
