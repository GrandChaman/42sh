/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_change_pgrp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 15:46:15 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/25 17:21:55 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "sh21.h"

static void		jc_change_pgrp_bg(t_jc_job *job)
{
	int			kill_res;
	t_list		*proc_list;
	t_jc_proc	*proc;

	proc_list = job->proc_list;
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
}

static void		jc_change_pgrp_fg(t_jc_job *job)
{
	int			kill_res;
	t_list		*proc_list;
	t_jc_proc	*proc;

	proc_list = job->proc_list;
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

void			jc_change_pgrp(t_jc_job *job, int mode)
{
	if (mode == BG)
		jc_change_pgrp_bg(job);
	else
		jc_change_pgrp_fg(job);
}
