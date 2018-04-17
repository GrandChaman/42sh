/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/06 17:27:58 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"

void 	bminus(void)
{
	t_ast *tree;
	int i;

	i = 0;
	tree = &sh21_get()->tree;
	while (i < NB_ESCAPED_QUOTE)
	{
		tree->esc_i[i++] = -1;
	}
}

int		func_word(t_ast_node *root)
{
	t_sh21			*sh21;
	t_fd_cleanup	*fd_cleanup;
	int				status;

	status = 0;
	if (!root)
		return (0);
	sh21 = sh21_get();
	bminus();
	root->content = format_word(&root->content);
	sh21->argv = split_args(root->content);
	sh21->argc = arrlen(sh21->argv);
	if (root->left)
		status = g_exec_fn[root->left->type](root->left);
	if (!status)
		status = sh21_exec(arrlen(sh21->argv), sh21->argv, &sh21->env.orig_env);
	sh21->status = status;
	fd_cleanup = sh21->tree.fd_cleanup;
	while (fd_cleanup)
	{
		fd_cleanup->fd_function(fd_cleanup);
		fd_cleanup = fd_cleanup->next;
	}
	del_arr(&sh21->argv);
	del_list((void **)&sh21->tree.fd_cleanup, &del_redir);
	return (status);
}
