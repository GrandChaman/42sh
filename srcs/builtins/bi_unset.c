/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:20:27 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/18 18:49:00 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"

int		bi_unset(int argc, char **argv, char ***environ, t_ast_node *root)
{
	int		i;

	(void)environ;
	(void)root;
	if (argc == 1)
	{
		ft_printf("unset: Too few arguments\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		ft_unsetenv(argv[i++], &sh21_get()->env.local_var);
	}
	return (0);
}
