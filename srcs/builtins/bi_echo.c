/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:44:45 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/14 20:53:21 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"

int		bi_echo(int argc, char **argv, char ***environ)
{
	int		i;
	int		n;

	(void)environ;
	if (argc <= 1)
	{
		ft_putchar('\n');
		return (0);
	}
	n = ft_strcmp(argv[1], "-n") == 0;
	i = 1 + n;
	while (i < argc)
	{
		ft_putstr(argv[i]);
		if (i != argc - 1)
			ft_putchar(' ');
		++i;
	}
	if (!n)
		ft_putchar('\n');
	return (0);
}
