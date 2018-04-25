/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:19:46 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/19 14:24:07 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	reset_job(t_ast_node *root)
{
	if (!root)
		return ;
	reset_job(root->condition_node);
	reset_job(root->left);
	reset_job(root->right);
	root->tag_gpid = -1;
}

int		func_while(t_ast_node *root)
{
	t_sh21			*sh21;
	t_fd_cleanup	*fd_cleanup;
	int				status;

	sh21 = sh21_get();
	status = 0;
	if (root->redir_node)
		status = g_exec_fn[root->redir_node->type](root->redir_node);
	if (!status)
	{
		while (!(status = g_exec_fn[root->left->type](root->left)))
		{
			if (sh21->signal == T_CTRL_C)
				return (1);
			status = g_exec_fn[root->right->type](root->right);
			reset_job(root);
		}
	}
	return (status);
}
