/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_io_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:59:29 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/15 16:38:13 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh21.h"

int		func_io_number(t_ast_node *root)
{
	if (sh21_get()->signal == T_CTRL_C)
		return (1);
	if (root->left)
		g_exec_fn[root->left->type](root->left);
	return (0);
}
