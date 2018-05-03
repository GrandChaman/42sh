/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:44:02 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/19 20:39:11 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"

int		bi_hash(int argc, char **argv, char ***environ, t_ast_node *root)
{
	t_sh21 *sh21;

	(void)argc;
	(void)argv;
	(void)environ;
	(void)root;
	sh21 = sh21_get();
	find_bin_paths(&sh21->env, environ);
	return (0);
}
