/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:38:41 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/26 13:31:25 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"
#include "job_control.h"

static void		quit_all_jobs(void)
{
	t_list		*job_list;
	t_jc_job	*job;

	job_list = jc_get()->job_list;
	while (job_list)
	{
		job = (t_jc_job*)job_list->content;
		killpg(job->pgid, SIGKILL);
		jc_set(job->tag, FG);
		job_list = job_list->next;
	}
}

int				bi_exit(int argc, char **argv, char ***environ,
	t_ast_node *root)
{
	(void)root;
	(void)environ;
	if (!(argc > 1 && !ft_strncmp(argv[1], "-f", 2)) && jc_get()->job_list)
	{
		ft_fprintf(2, "Jobs are still running. Please close them before"
			" exiting\n");
		return (1);
	}
	else if (jc_get()->job_list)
		quit_all_jobs();
	del_sh21_exit();
	ft_exit(0, NULL);
	return (0);
}

void			ft_exit(int err, const char *s)
{
	t_sh21 *sh21;

	sh21 = sh21_get();
	if (err)
		ft_error(err, s);
	exit(err);
}
