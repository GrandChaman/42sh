/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:23:38 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/25 21:42:13 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"
#include "builtins.h"
#include "env.h"

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
		print_one_jobs(job->tag);
		tmp = tmp->next;
	}
}

static int		print_one_job_routine(t_jc_job *job)
{
	t_list		*proc_list;
	t_jc_proc	*proc;

	proc_list = job->proc_list;
	proc = (t_jc_proc*)(proc_list->content);
	ft_printf("[%d] + %d %-*s", job->tag, proc->pid, 11,
		g_jc_status_string[proc->status]);
	if (proc->status == KILLED && proc->rvalue > 0 && proc->rvalue <= 32)
		ft_printf("(Signal : %s (%d))", sys_siglist[proc->rvalue], proc->rvalue);
	else if (proc->status == KILLED)
		ft_printf("(Signal : %d)", proc->rvalue);
	else if (proc->status == DONE)
		ft_printf("(Exit code : %d)", proc->rvalue);
	else
		ft_printf("%*s", 18, " ");
	ft_printf(" %s\n", proc->cmd);
	while ((proc_list = proc_list->next))
	{
		proc = (t_jc_proc*)(proc_list->content);
		ft_printf("%*s%d %-*s", 6 + ft_numlen(job->tag), " ", proc->pid, 11,
			g_jc_status_string[proc->status]);
		if (proc->status == KILLED && proc->rvalue > 0 && proc->rvalue <= 32)
			ft_printf("(Signal : %s (%d))", sys_siglist[proc->rvalue], proc->rvalue);
		else if (proc->status == KILLED)
			ft_printf("(Signal : %d)", proc->rvalue);
		else if (proc->status == DONE)
			ft_printf("(Exit code : %d)", proc->rvalue);
		else
		ft_printf("%*s", 18, " ");
		ft_printf(" %s\n", proc->cmd);
	}
	return (1);
}

int				print_one_jobs(int ntag)
{
	t_list		*tmp;

	tmp = jc_get()->job_list;
	while (tmp != NULL)
	{
		if (ntag == ((t_jc_job*)(tmp->content))->tag)
			print_one_job_routine((t_jc_job*)(tmp->content));
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
