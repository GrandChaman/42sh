/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_args_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 13:43:49 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/26 14:25:27 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			args_init(t_hist_args *args)
{
	args->c = 0;
	args->p = 0;
	args->s = 0;
	args->d = 0;
	args->d_val = 0;
	args->awrn = 0;
	args->err = 0;
	args->argv_count = 1;
	args->concate_argv = NULL;
}

static void		awrn_handle(t_hist_args *args, char *str)
{
	if (*str == 'a' && !args->awrn)
		args->awrn = 'a';
	else if (*str == 'w' && !args->awrn)
		args->awrn = 'w';
	else if (*str == 'r' && !args->awrn)
		args->awrn = 'r';
	else if (*str == 'n' && !args->awrn)
		args->awrn = 'n';
}

static int		handle_arg(t_hist_args *args, char **arg)
{
	char	*str;

	str = *arg;
	while (*str)
	{
		if (!ft_strchr("awrncdps", *str))
			return ((args->err = INVARG));
		if (*str == 'c')
			args->c = 1;
		else if (*str == 'p')
			args->p = 1;
		else if (*str == 's')
			args->s = 1;
		else if (*str == 'd' && (args->d = 1))
			return ('d');
		else if (ft_strchr("awrn", *str) != NULL)
		{
			if (args->awrn != 0)
				return ((args->err = AWRN_ERR));
			awrn_handle(args, str);
		}
		++*arg;
		++str;
	}
	return (0);
}

static void		process_args(char *arg, t_hist_args *args, int ac, char **av)
{
	++arg;
	if (handle_arg(args, &arg) == 'd')
	{
		++arg;
		if (*arg && ft_isdigit(*arg))
		{
			args->d_val = ft_atoi(arg);
			arg = av[++args->argv_count];
		}
		else if (args->argv_count < ac - 1)
		{
			arg = av[++args->argv_count];
			if (*arg && ft_isdigit(*arg))
			{
				args->d_val = ft_atoi(arg);
				arg = av[++args->argv_count];
			}
			else
				args->err = D_ERR;
		}
		else
			args->err = D_ERR;
	}
}

void			read_args(t_hist_args *args, int argc, char **argv)
{
	char *arg;

	args->argv_count = 1;
	while (args->argv_count < argc)
	{
		arg = argv[args->argv_count];
		if (*arg == '-')
			process_args(arg, args, argc, argv);
		else
		{
			args->concate_argv = concate_array(argv + args->argv_count);
			return ;
		}
		++args->argv_count;
	}
}
