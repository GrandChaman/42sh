/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 13:13:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/23 13:21:26 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <signal.h>
#include "sh21.h"

static void	jc_change_pgrp(t_jc_job *job, int mode)
{
	if (mode == BG)
	{
		ft_printf("[%d] %d (%C)\n", job->tag, job->pgid, 8675);
		if (tcsetpgrp(STDIN_FILENO, getpgrp()))
			ft_exit(errno, "tcsetpgrp");
		return ;
	}
	//ft_printf("[%d] %d (%C)\n", job->tag, job->pgid, 8673);
	if (killpg(job->pgid, SIGCONT))
		ft_exit(errno, "killpg");
	jc_get()->fg_job = job;
	if (tcsetpgrp(STDIN_FILENO, job->pgid))
		ft_exit(errno, "tcsetpgrp"); //decommenter apres
}

static int	jc_wait(t_jc_job *job, int mode, int *should_update)
{
	int status;

	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	*should_update = 1;
	if (mode == BG)
	{
		if (!waitpid(-job->pgid, &status, WUNTRACED | WNOHANG))
			*should_update = 0;
	}
	else
	{
		waitpid(-job->pgid, &status, WUNTRACED);
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp(0, getpgrp());
		signal(SIGTTOU, SIG_DFL);
	}
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (status);
}

int			jc_set(t_jc_tag tag, int mode)
{
	t_list		*jb_list;
	t_jc_job*	job;
	int			res;
	int			should_update;

	jb_list = jc_get()->job_list;
	while (jb_list)
	{
		job = ((t_jc_job*)jb_list->content);
		if (job->tag == tag)
		{
			jc_change_pgrp(job, mode);
			res = jc_wait(job, mode, &should_update);
			if (should_update)
				jc_update(job, res);
			else
				res = 0;
			return (res);
		}
		jb_list = jb_list->next;
	}
	return (0);
}
