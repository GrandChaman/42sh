/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:20:27 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/19 12:40:29 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"

int		bi_unset(int argc, char **argv, char ***environ)
{
	int		i;

	(void)environ;
	if (argc == 1)
	{
		ft_printf("%[RED]21sh%[NC]: unset: Too few arguments\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		ft_unsetenv(argv[i++], &sh21_get()->env.local_var);
	}
	return (0);
}
