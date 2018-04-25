/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_args_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 13:43:49 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/25 16:41:03 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sh21.h"

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

int				handle_arg(t_hist_args *args, char **arg)
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
		else if (*str == 'd')
		{
			args->d = 1;
			return ('d');
		}
		else if (strchr("awrn", *str) != NULL)
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

void print_hhh(t_hist_args flags)
{
	flags.err ? ft_printf("ERROR") : (0);
	flags.d ? ft_printf("D:%i", flags.d_val) : (0);
	flags.c ? ft_printf("C") : (0);
	flags.p ? ft_printf("P") : (0);
	flags.s ? ft_printf("S") : (0);
	flags.awrn ? ft_printf("%c", flags.awrn) : (0);
}


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
}

#define Dreturn ft_printf("%i\n", __LINE__); return ;

void			read_args(t_hist_args *args, int argc, char **argv)
{
	int err;

	args->argv_count = 1;
	while (args->argv_count < argc)
	{
		char  *arg = argv[args->argv_count];
		if (*arg == '-')
		{
			++arg;
			if ((err = handle_arg(args, &arg)) == 'd')
			{
				++arg;
				if (*arg && isdigit(*arg))
				{
					args->d_val = atoi(arg);
					arg = argv[++args->argv_count];
				}
				else if (args->argv_count < argc - 1)
				{
					arg = argv[++args->argv_count];
					if (*arg && isdigit(*arg))
					{
						args->d_val = atoi(arg);
						arg = argv[++args->argv_count];
					}
					else
						args->err = D_ERR;
				}
				else
					args->err = D_ERR;
			}
			else if (err == -1)
			{
				args->err = AWRN_ERR;
				return ;
			}
			else if (err < 0)
				return ;
		}
		else
			return ;
		++args->argv_count;
	}
}
