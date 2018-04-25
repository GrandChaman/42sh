/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/24 16:26:29 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"

int		func_word(t_ast_node *root)
{
	t_sh21			*sh21;
	t_fd_cleanup	*fd_cleanup;
	int				status;
	char			**argv;

	status = 0;
	if (!root)
		return (0);
	sh21 = sh21_get();
	root->content = format_word(root->content, root);
	argv = split_args(root->content, root);
	if (root->redir_node)
		status = g_exec_fn[root->redir_node->type](root->redir_node);
	if (!status)
		status = sh21_exec(arrlen(argv), argv, &sh21->env.orig_env);
	sh21->status = status;
	fd_cleanup = sh21->tree.fd_cleanup;
	while (fd_cleanup)
	{
		fd_cleanup->fd_function(fd_cleanup);
		fd_cleanup = fd_cleanup->next;
	}
	del_arr(&argv);
	del_list((void **)&sh21->tree.fd_cleanup, &del_redir);
	return (status);
}
