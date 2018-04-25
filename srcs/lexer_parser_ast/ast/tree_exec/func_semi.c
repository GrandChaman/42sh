/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_semi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:59:29 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/15 16:37:26 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh21.h"

int		func_semi(t_ast_node *root)
{
	int ret;

	ret = 0;
	if (sh21_get()->signal == T_CTRL_C)
		return (1);
	if (root->left)
		ret = g_exec_fn[root->left->type](root->left);
	if (root->right)
		ret = g_exec_fn[root->right->type](root->right);
	return (ret);
}
