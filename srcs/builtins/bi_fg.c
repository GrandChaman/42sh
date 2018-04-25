/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:19:09 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/24 14:29:13 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"
#include "builtins.h"
#include "env.h"


static int		print_one_jobs_2(int tague)
{
	t_list	*tmp;
	t_jc	*jobs_struct;
	t_list	*autre;

	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		if (((t_jc_job*)(tmp->content))->tag == tague)
		{
			autre = ((t_jc_job*)(tmp->content))->proc_list;
			while (autre != NULL)
			{
				ft_printf("%s\n",((t_jc_proc*)(autre->content))->cmd);
				autre = autre->next;
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int					check_jobs(int tague)
{
	t_list	*tmp;
	t_jc	*jobs_struct;

	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		if (tague == ((t_jc_job*)(tmp->content))->tag)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void			bi_fg_loop(char **argv)
{
	if (argv[1][0] != '%' || !argv[1][1])
		ft_fprintf(2, "42sh: fg: %s: no such job\n", argv[1]);
	else if (argv[1][1] == '%' || argv[1][1] == '+')
	{
		if (!(check_jobs(get_last_jobs())))
			ft_fprintf(2, "42sh: fg: %s: no such job\n", argv[1]);
		print_one_jobs_2(get_last_jobs());
		jc_set(get_last_jobs(), FG);
	}
	else if (argv[1][1] == '-')
	{
		if (!(check_jobs(get_last_last_jobs())))
			ft_fprintf(2, "42sh: fg: %s: no such job\n", argv[1]);
		print_one_jobs_2(get_last_last_jobs());
		jc_set(get_last_last_jobs(), FG);
	}
	else
	{
		if (!(check_jobs(ft_atoi(argv[1] + 1))))
			ft_fprintf(2, "42sh: fg: %s: no such job\n", argv[1]);
		print_one_jobs_2(ft_atoi(argv[1] + 1));
		jc_set(ft_atoi(argv[1] + 1), FG);
	}
}

int					bi_fg(int argc, char **argv, char ***environ,
	t_ast_node *root)
{
	(void)environ;
	(void)root;
	if (argc == 1)
	{
		if (!(check_jobs(get_last_jobs())))
			ft_fprintf(2, "42sh: fg: No current job\n");
		print_one_jobs_2(get_last_jobs());
		jc_set(get_last_jobs(), FG);
	}
	else if (argc > 2)
		ft_fprintf(2, "42sh: fg: Too much arguments\n");
	else
		bi_fg_loop(argv);
	return (0);
}
