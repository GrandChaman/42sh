/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 13:13:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/22 15:07:59 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <signal.h>

static void	jc_change_pgrp(t_jc_job *job, int mode)
{
	if (mode == BG)
	{
		ft_printf("[%d] %d (%C)\n", job->tag, job->pgid, 8675);
		if (tcsetpgrp(STDIN_FILENO, getpgrp()))
			ft_perror("tcsetpgrp", "System call failed");
		return ;
	}
	ft_printf("[%d] %d (%C)\n", job->tag, job->pgid, 8673);
	if (killpg(job->pgid, SIGCONT))
		ft_perror("killpg", "System call failed");
	jc_get()->fg_job = job;
	if (tcsetpgrp(STDIN_FILENO, job->pgid));
		ft_perror("tcsetpgrp", "System call failed");
}

static int	jc_wait(t_jc_job *job, int mode)
{
	int status;

	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	if (mode == BG)
		waitpid(-job->pgid, &status, WUNTRACED | WNOHANG);
	else
	{
		waitpid(-job->pgid, &status, WUNTRACED);
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp(0, getpgrp());
		signal(SIGTTOU, SIG_DFL);
	}
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);

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
			jc_update(job, res);
			return (res);
		}
		jb_list = jb_list->next;
	}
	return (0);
}
