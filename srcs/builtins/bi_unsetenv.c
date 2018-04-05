/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:43:37 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/14 21:32:30 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"

int		bi_unsetenv(int argc, char **argv, char ***environ)
{
	int		i;

	if (argc == 1)
	{
		ft_printf("%[RED]21sh%[NC]: unsetenv: Too few arguments\n");
		return (1);
	}
	i = 1;
	while (i < argc)
		ft_unsetenv(argv[i++], environ);
	return (0);
}
