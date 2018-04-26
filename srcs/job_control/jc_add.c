/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:58:28 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/27 01:00:38 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "job_control.h"

static void	jc_add_routine(t_jc_job *job, pid_t npid, char *cmd)
{
	t_jc_proc	proc;

<<<<<<< HEAD
	if (!job->proc_list)
	{
		if (setpgid(npid, npid) < 0)
		{
			ft_exit(errno, "setpgid");
		}
		job->pgid = npid;
	}
	else if (setpgid(npid, job->pgid) < 0)
		ft_exit(errno, "setpgid");
=======
>>>>>>> Fixed big race condition on setpgid
	proc.pid = npid;
	proc.cmd = cmd;
	proc.status = NONE;
	if (setpgid(npid, (!job->proc_list ? npid : job->pgid)) < 0)
	{
		if (!job->proc_list)
			job->pgid = -1;
	}
	else if (!job->proc_list)
		job->pgid = npid;
	ft_lstpush_back(&job->proc_list, &proc, sizeof(t_jc_proc));
	if (job->pgid == -1)
		jc_update_job(job);
	return ;
}

void		jc_add(t_jc_tag jtag, pid_t npid, char *cmd)
{
	t_list		*jb_list;
	t_jc_job	*tmp;

	jb_list = jc_get()->job_list;
	while (jb_list)
	{
		tmp = ((t_jc_job*)jb_list->content);
		if (tmp->tag == jtag)
			jc_add_routine(tmp, npid, cmd);
		jb_list = jb_list->next;
	}
}
