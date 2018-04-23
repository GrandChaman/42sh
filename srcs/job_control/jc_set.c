/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 13:13:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/23 17:46:34 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <signal.h>
#include "sh21.h"

static void	jc_change_pgrp(t_jc_job *job, int mode)
{
	int kill_res;

	if (mode == BG)
	{
		ft_printf("[%d] %d (%C)\n", job->tag, job->pgid, 8675);
		if (tcsetpgrp(STDIN_FILENO, getpgrp()))
			ft_exit(errno, "tcsetpgrp");
		if (job->status == SUSPENDED)
		{
			kill_res = killpg(job->pgid, SIGCONT);
			if (kill_res != 0 && errno != EPERM)
				ft_exit(errno, "killpg");
		}
			job->status = RUNNING;
		return ;
	}
	if (job->status == SUSPENDED)
	{
		kill_res = killpg(job->pgid, SIGCONT);
		if (kill_res != 0 && errno != EPERM)
			ft_exit(errno, "killpg");
	}
	job->status = RUNNING;
	jc_get()->fg_job = job;
	if (tcsetpgrp(STDIN_FILENO, job->pgid))
		ft_exit(errno, "tcsetpgrp");

}

static int	jc_wait(t_jc_job *job, int mode, int *should_update)
{
	int status;
	int wait_res;

	*should_update = 1;
	if (mode == BG)
	{
		*should_update = 0; //TODO
		while ((wait_res = waitpid(-job->pgid, &status, WUNTRACED | WNOHANG))
			!= 0)
			{
				if (wait_res < 0)
					ft_exit(errno, "waitpid");
				else
					*should_update = 1;
				ft_printf("Alatreub");
			}
	}
	else
	{
		ft_fprintf(2, "Toto 1\n");
		while ((wait_res = waitpid(-job->pgid, &status, WUNTRACED)))
			if (wait_res < 0 && errno != ECHILD)
				ft_exit(errno, "waitpid");
			else if (wait_res < 0 && errno == ECHILD)
				break ;
		ft_fprintf(2, "Toto 2\n");
		tcsetpgrp(0, getpgrp());
	}
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
			// DEBUG
			t_list *toto;
			ft_fprintf(2, "{green}%d - Call jc_set\n{eoc}", getpid());
			toto = job->pid_list;
			while (toto)
			{
				ft_printf("PID : {magenta}%d{eoc}\n", *((int*)toto->content));
				toto = toto->next;
			}
			// DEBUG
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
