/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_args_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:06:25 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/23 18:23:06 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "builtins.h"

t_hist_args		*args_create(void)
{
	t_hist_args *args;

	args = malloc(sizeof(t_hist_args));
	args->c = 0;
	args->d = 0;
	args->d_val = 0;
	args->p = 0;
	args->s = 0;
	args->awrn = 0;
	args->err = 0;
	return (args);
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

int				handle_arg(t_hist_args *args, char **arg)
{
	char	*str;

	str = *arg;
	while (*str)
	{
		if (*str == 'c')
			args->c = 1;
		else if (*str == 'p')
			args->p = 1;
		else if (*str == 's')
			args->s = 1;
		else if (strchr("awrn", *str) != NULL)
		{
			if (args->awrn != 0)
				return (-1);
			awrn_handle(args, str);
		}
		else
			return ((args->d = (*str == 'd')) ? 'd' : INVARG);
		++*arg;
		++str;
	}
	return (0);
}

void			read_args(t_hist_args *args, int argc, char **argv)
{
	int		idx;
	int		err;
	char	*arg;

	idx = 1;
	while (idx < argc)
	{
		arg = argv[idx];
		if (*arg == '-')
		{
			++arg;
			if ((err = handle_arg(args, &arg)) == 'd')
			{
				++arg;
				if (*arg && isdigit(*arg))
					args->d_val = atoi(arg);
				else if (idx < argc - 1)
				{
					arg = argv[++idx];
					if (*arg && isdigit(*arg))
						args->d_val = atoi(arg);
					else
						args->err = D_ERR;
				}
				else
					args->err = D_ERR;
			}
			else if (err < 0)
			{
				args->err = AWRN_ERR;
				return ;
			}
		}
		else
			return ;
		++idx;
	}
}
