/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 13:13:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/05/15 16:03:48 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "sh21.h"

static void	jc_wait_on_bg(t_jc_job *job)
{
	jc_set_job_as_running(job);
	jc_get()->fg_job = NULL;
}

static int	jc_wait(t_jc_job *job, int mode)
{
	int		status;
	int		wait_res;
	t_list	*proc_list;

	if (!(status = 0) && mode == BG)
		jc_wait_on_bg(job);
	else if ((proc_list = job->proc_list) || 1)
	{
		while (proc_list)
		{
			wait_res = waitpid(((t_jc_proc*)proc_list->content)->pid,
				&status, WUNTRACED);
			if (wait_res < 0 && errno != ECHILD)
				ft_exit(errno, "waitpid");
			else if (wait_res < 0 && errno == ECHILD)
				break ;
			jc_update_proc(((t_jc_proc*)proc_list->content), status);
			status = ((t_jc_proc*)proc_list->content)->rvalue;
			proc_list = proc_list->next;
		}
		jc_garbage_collector(jc_get());
		if (get_ft_shell()->is_a_tty)
			tcsetpgrp(sh21_get()->tty, getpgrp());
	}
	return (status);
}

int			jc_set(t_jc_tag tag, int mode)
{
	t_list		*jb_list;
	t_jc_job	*job;
	int			res;

	jb_list = jc_get()->job_list;
	while (jb_list)
	{
		job = ((t_jc_job*)jb_list->content);
		if (job->tag == tag)
		{
			jc_change_pgrp(job, mode);
			res = jc_wait(job, mode);
			jc_get()->fg_job = NULL;
			return (res);
		}
		jb_list = jb_list->next;
	}
	return (0);
}
