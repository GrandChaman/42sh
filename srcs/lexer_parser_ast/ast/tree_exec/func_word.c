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

int		func_word(t_ast_node *root)
{
	t_sh21			*sh21;
	// t_fd_cleanup	*fd_cleanup;
	int				status;

	status = 0;
	if (!root)
		return (0);
	sh21 = sh21_get();
	root->content = format_word(&root->content);
	sh21->argv = split_args(root->content);
	if (root->tag_gpid < 0)
		root->tag_gpid = jc_create_tag();
	if (!status)
		status = sh21_exec(sh21->argv, &sh21->env.orig_env, root); //add tag_gpid
	sh21->status = status;

	del_arr(&sh21->argv);
	return (status);
}

// int 	change_fd(t_ast_node *root)
// {
// 	if (root->piped_cmd)
// 	{
// 		root->tmp_fd = dup(root->pipe_side);
// 		close(root->pipe_side ? 0 : 1);
// 		dup2(root->pipe_fd, root->pipe_side);
// 		close(root->pipe_fd);
// 	}
// 	if (root->redir_node)
// 		status = g_exec_fn[root->redir_node->type](root->redir_node);
// }
//
// int 	reset_fd(t_ast_node *root)
// {
// 	fd_cleanup = sh21->tree.fd_cleanup;
// 	while (fd_cleanup)
// 	{
// 		fd_cleanup->fd_function(fd_cleanup);
// 		fd_cleanup = fd_cleanup->next;
// 	}
// 	del_list((void **)&sh21->tree.fd_cleanup, &del_redir);
// 	if (root->piped_cmd)
// 	{
// 		if (root->piped_cmd)
// 		{
// 			dup2(root->tmp_fd, root->pipe_side);
// 			close(root->tmp_fd);
// 		}
// 	}
// 	//reset pipe
// }
