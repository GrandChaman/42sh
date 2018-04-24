/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:23:38 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/24 14:29:03 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"
#include "builtins.h"
#include "env.h"

static void		print_jobs(void)
{
	t_list	*tmp;
	t_jc	*jobs_struct;
	t_list	*autre;

	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		ft_printf("[%d] PGID:%d\n", ((t_jc_job*)(tmp->content))->tag,
			((t_jc_job*)(tmp->content))->pgid);
		autre = ((t_jc_job*)(tmp->content))->pid_list;
		while (autre != NULL)
		{
			ft_printf("%s\n", g_jc_status_string[((t_jc_proc*)(autre->content))->status]);
			autre = autre->next;
		}
		tmp = tmp->next;
	}
}

static int		print_one_jobs(int tague)
{
	t_list	*tmp;
	t_jc	*jobs_struct;
	t_list	*autre;

	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		if (tague == ((t_jc_job*)(tmp->content))->tag)
		{
			ft_printf("[%d] PGID:%d\n", ((t_jc_job*)(tmp->content))->tag,
				((t_jc_job*)(tmp->content))->pgid);
			autre = ((t_jc_job*)(tmp->content))->pid_list;
			while (autre != NULL)
			{
				ft_printf("%s\n", g_jc_status_string[((t_jc_proc*)(autre->content))->status]);
				autre = autre->next;
			}
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
