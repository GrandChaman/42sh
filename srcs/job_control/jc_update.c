/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 13:33:03 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/24 14:40:44 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void		jc_update_all(void)
{
	// t_jc		*jc;
	// t_list	*job_list;
	// t_jc_job	*job;
	// int			status;
    //
	// jc = jc_get();
	// job_list = jc->job_list;
	// while (job_list)
	// {
	// 	job = ((t_jc_job*)job_list->content);
	// 	if (waitpid(-job->pgid, &status, WUNTRACED | WNOHANG))
	// 		jc_update(((t_jc_job*)job_list->content), status);
	// 	job_list = job_list->next;
	// }
}

void		jc_update(t_jc_job *job, int status)
{
	// t_jc	*jc;
    //
	// jc = jc_get();
	// if (WIFEXITED(status) || WIFSIGNALED(status))
	// {
	// 	job->status = (WIFEXITED(status) ? DONE : KILLED);
	// 	if (job != jc->fg_job || job->status == KILLED)
	// 		jc_print(job);
	// 	if (job == jc->fg_job)
	// 		jc->fg_job = NULL;
	// 	jc_delete_tag(job->tag);
	// 	return ;
	// }
	// else if (WIFSTOPPED(status))
	// 	job->status = SUSPENDED;
	// else
	// 	job->status = RUNNING;
	// if (job != jc->fg_job)
	// 	jc_print(job);

	// t_jc		*jc;
	// t_list		*proc_list;
	// t_jc_proc	*proc;
	// int			wait_res;
	// int			status;
    //
	// jc = jc_get();
	// proc_list = job->pid_list;
	// while (proc_list)
	// {
	// 	proc = (t_jc_proc*)proc_list->content;
	// 	proc_list = proc_list->next;
	// 	if ((wait_res = waitpid(proc->pid, &status, WUNTRACED | WNOHANG) == 0)
    //
	// }

}
