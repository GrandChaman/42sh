/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_args_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 13:43:49 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/25 14:21:48 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sh21.h"

#define AF			1 << 0
#define WF			1 << 1
#define RF			1 << 2
#define NF			1 << 3
#define D_ERR		1 << 4
#define AWRN_ERR	1 << 5
#define INVARG		1 << 6

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
		else if (strchr("awrn", *str) != NULL)
		{
			if (args->awrn != 0)
				return ((args->err = AWRN_ERR));
			awrn_handle(args, str);
		}
		else
			return ((args->d = (*str == 'd')) ? 'd' : D_ERR);
		++*arg;
		++str;
	}
	return (0);
}

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
					args->d_val = atoi(arg);
				else if (args->argv_count < argc - 1)
				{
					arg = argv[++args->argv_count];
					if (*arg && isdigit(*arg))
						args->d_val = atoi(arg);
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
				return;
		}
		else
			return;
		++args->argv_count;
	}
}
