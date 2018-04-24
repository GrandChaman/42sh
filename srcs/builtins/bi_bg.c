/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:21:43 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/24 14:29:18 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int				get_last_jobs(void)
{
	t_list	*tmp;
	t_jc	*jobs_struct;
	int		tague;

	tague = -1;
	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		tague = ((t_jc_job*)(tmp->content))->tag;
		tmp = tmp->next;
	}
	return (tague);
}

int				get_last_last_jobs(void)
{
	t_list	*tmp;
	t_jc	*jobs_struct;
	int		tague;
	int		stock;

	tague = -1;
	stock = -1;
	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		stock = tague;
		tague = ((t_jc_job*)(tmp->content))->tag;
		tmp = tmp->next;
	}
	return (stock);
}

static void			bi_bg_loop(char **argv, int i)
{
	if (argv[i][0] != '%' || !argv[i][1])
		ft_fprintf(2, "42sh: bg: %s: no such job\n", argv[i]);
	else if (argv[i][1] == '%' || argv[i][1] == '+')
	{
		if (!(check_jobs(get_last_jobs())))
			ft_fprintf(2, "42sh: bg: %s: no such job\n", argv[i]);
		jc_set(get_last_jobs(), BG);
	}
	else if (argv[i][1] == '-')
	{
		if (!(check_jobs(get_last_last_jobs())))
			ft_fprintf(2, "42sh: bg: %s: no such job\n", argv[i]);
		jc_set(get_last_last_jobs(), BG);
	}
	else
	{
		if (!(check_jobs(ft_atoi(argv[i] + 1))))
			ft_fprintf(2, "42sh: bg: %s: no such job\n", argv[i]);
		jc_set(ft_atoi(argv[i] + 1), BG);
	}
}

int					bi_bg(int argc, char **argv,
	char ***environ, t_ast_node *root)
{
	int i;
    
	i = 1;
	(void)environ; // rajouter msg si c est deja en backgroung;
	(void)root;
	if (argc == 1)
	{
		if (!(check_jobs(get_last_jobs())))
			ft_fprintf(2, "42sh: bg: No current job\n");
		jc_set(get_last_jobs(), BG);
	}
	else
	{
		while (i < argc)
		{
			bi_bg_loop(argv, i);
			i++;
		}
	}
	return (0);
}
