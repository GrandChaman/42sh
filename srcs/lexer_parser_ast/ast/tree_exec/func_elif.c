/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_elif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:19:12 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/18 23:19:14 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		func_elif(t_ast_node *root)
{
	int status;

	status = 0;
	if (sh21_get()->signal == T_CTRL_C)
		return (1);
	if (!g_exec_fn[root->condition_node->type](root->condition_node))
		status = g_exec_fn[root->left->type](root->left);
	else if (root->right)
		status = g_exec_fn[root->right->type](root->right);
	return (status);
}
