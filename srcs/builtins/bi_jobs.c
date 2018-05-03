/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:23:38 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/26 22:01:16 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"
#include "builtins.h"
#include "env.h"

static int		print_one_job_routine(t_jc_job *job)
{
	t_list		*p_list;
	t_jc_proc	*p;

	p_list = job->proc_list;
	p = (t_jc_proc*)(p_list->content);
	ft_printf("[%d] + %d %-*s", job->tag, p->pid, 11,
		g_jc_status_string[p->status]);
	while (p_list)
	{
		p = (t_jc_proc*)(p_list->content);
		if (p_list->prev)
			ft_printf("%*s%d %-*s", 6 + ft_numlen(job->tag), " ", p->pid, 11,
				g_jc_status_string[p->status]);
		if (p->status == KILLED && p->rvalue > 0 && p->rvalue <= 32)
			ft_printf("(Signal : %s (%d))", sys_siglist[p->rvalue], p->rvalue);
		else if (p->status == KILLED)
			ft_printf("(Signal : %d)", p->rvalue);
		else if (p->status == DONE)
			ft_printf("(Exit code : %d)", p->rvalue);
		else
			ft_printf("%*s", 18, " ");
		ft_printf(" %s\n", p->cmd);
		p_list = p_list->next;
	}
	return (1);
}

static void		print_jobs(void)
{
	t_list		*tmp;
	t_jc		*jobs_struct;
	t_jc_job	*job;

	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp)
	{
		job = ((t_jc_job*)(tmp->content));
		tmp = tmp->next;
		if (job && job->proc_list)
			print_one_job_routine(job);
	}
}

int				print_one_jobs(int ntag)
{
	t_list		*tmp;

	tmp = jc_get()->job_list;
	while (tmp != NULL)
	{
		if (ntag == ((t_jc_job*)(tmp->content))->tag)
		{
			print_one_job_routine((t_jc_job*)(tmp->content));
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void		bi_jobs_loop(char **argv, int i)
{
	if (argv[i][0] != '%' || !argv[i][1])
		ft_fprintf(2, "42sh: jobs: %s: no such job\n", argv[i]);
	else if (argv[i][1] == '%' || argv[i][1] == '+')
	{
		if (!(print_one_jobs(get_last_jobs())))
			ft_fprintf(2, "42sh: jobs: %s: no such job\n", argv[i]);
	}
	else if (argv[i][1] == '-')
	{
		if (!(print_one_jobs(get_last_last_jobs())))
			ft_fprintf(2, "42sh: jobs: %s: no such job\n", argv[i]);
	}
	else
	{
		if (!(print_one_jobs(ft_atoi(argv[i] + 1))))
			ft_fprintf(2, "42sh: jobs: %s: no such job\n", argv[i]);
	}
}

int				bi_jobs(int argc, char **argv,
	char ***environ, t_ast_node *root)
{
	int i;

	i = 1;
	(void)environ;
	(void)root;
	if (argc == 1)
	{
		print_jobs();
		return (0);
	}
	while (i < argc)
	{
		bi_jobs_loop(argv, i);
		i++;
	}
	return (0);
}
