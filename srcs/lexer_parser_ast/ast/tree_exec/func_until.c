/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_until.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:59:29 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/24 18:13:35 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh21.h"

int		func_until(t_ast_node *root)
{
	t_sh21			*sh21;
	int				status;

	sh21 = sh21_get();
	status = 0;
	if (root->redir_node)
		status = g_exec_fn[root->redir_node->type](root->redir_node);
	if (!status)
	{
		while (g_exec_fn[root->left->type](root->left))
		{
			if (sh21->signal == T_CTRL_C)
				return (1);
			status = g_exec_fn[root->right->type](root->right);
			reset_job(root);
		}
	}
	return (status);
}
