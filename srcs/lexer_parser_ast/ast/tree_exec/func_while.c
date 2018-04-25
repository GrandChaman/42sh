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
		while (!g_exec_fn[root->left->type](root->left))
			status = g_exec_fn[root->right->type](root->right);
	fd_cleanup = sh21->tree.fd_cleanup;
	while (fd_cleanup)
	{
		fd_cleanup->fd_function(fd_cleanup);
		fd_cleanup = fd_cleanup->next;
	}
	del_list((void **)&sh21->tree.fd_cleanup, &del_redir);
	return (status);
}
