/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:30:13 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/25 12:42:00 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int			find_pgid(int tague)
{
	t_list	*tmp;
	t_jc	*jobs_struct;

	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		if (tague == ((t_jc_job*)(tmp->content))->tag)
			return (((t_jc_job*)(tmp->content))->pgid);
		tmp = tmp->next;
	}
	return (0);
}

static void			print_signal(void)
{
	ft_printf("1) SIGHUP\n2) SIGINT\n3) SIGQUIT\n4) SIGILL\n"
			"5) SIGTRAP\n6) SIGABRT\n7) SIGEMT\n8) SIGFPE\n"
			"9) SIGKILL\n10) SIGBUS\n11) SIGSEGV\n12) SIGSYS\n"
			"13) SIGPIPE\n14) SIGALRM\n15) SIGTERM\n16) SIGURG\n"
			"17) SIGSTOP\n18) SIGTSTP\n19) SIGCONT\n20) SIGCHLD\n"
			"21) SIGTTIN\n22) SIGTTOU\n23) SIGIO\n24) SIGXCPU\n"
			"25) SIGXFSZ\n26) SIGVTALRM\n27) SIGPROF\n28) SIGWINCH\n"
			"29) SIGINFO\n30) SIGUSR1\n31) SIGUSR2\n");
}

static int			flag_kill(int *i, char **argv, int *sinal)
{
	int stock;

	stock = 0;
	while (argv[*i] && argv[*i][0] == '-')
	{
		if (argv[*i][1] == 'l' && stock == 0)
		{
			print_signal();
			stock = 1;
			return (1);
		}
		else if (ft_atoi(argv[*i] + 1))
		{
			*sinal = ft_atoi(argv[*i] + 1);
			return (0);
		}
		else
		{
			ft_fprintf(2, "kill: usage: [-l | -SIGNAL]\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int			bi_kill_loop(char **argv, int i, int *stock)
{
	if (argv[i][1] == '%' || argv[i][1] == '+')
	{
		if (!(*stock = find_pgid(get_last_jobs())))
		{
			ft_fprintf(2, "42sh: kill: %s: no such job\n", argv[i]);
			return (1);
		}
	}
	else if (argv[i][1] == '-')
	{
		if (!(*stock = find_pgid(get_last_last_jobs())))
		{
			ft_fprintf(2, "42sh: kill: %s: no such job\n", argv[i]);
			return (1);
		}
	}
	else
	{
		if (!(*stock = find_pgid(ft_atoi(argv[i] + 1))))
		{
			ft_fprintf(2, "42sh: kill: %s: no such job\n", argv[i]);
			return (1);
		}
	}
	return (0);
}

int					bi_kill(int argc, char **argv,
	char ***environ, t_ast_node *root)
{
	int i;
	int stock;
	int sinal;

	(void)environ;
	(void)root;
	if ((sinal = 15) && argc == 1)
		return (ft_fprintf(2, "kill: usage: [-l | -SIGNAL]\n") && 1);
	if ((i = 1) && flag_kill(&i, argv, &sinal))
		return (0);
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '%')
		{
			if (bi_kill_loop(argv, i, &stock))
				return (1);
			killpg(stock, sinal);
		}
		else
			kill(ft_atoi(argv[i]), sinal);
	}
	return (0);
}
