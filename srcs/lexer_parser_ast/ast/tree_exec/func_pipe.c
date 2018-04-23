/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/16 14:57:57 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		func_pipe_right(t_ast_node *root, int pipefd[2])
{
	int		status;

	status = 0;
	if (root->right)
	{
		root->right->piped_cmd = 1 + root->piped_cmd;
		root->right->pipe_fd[0] = pipefd[0];
		root->left->pipe_to_close = pipefd[1];
		status = g_exec_fn[root->right->type](root->right);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	return (status);
}

void 	func_pipe_left(t_ast_node *root, int pipefd[2])
{
	root->left->piped_cmd = 1 + root->piped_cmd;
	root->left->pipe_fd[0] = root->pipe_fd[0];
	root->left->pipe_fd[1] = pipefd[1];
	root->left->pipe_to_close = pipefd[0];
	g_exec_fn[root->left->type](root->left);
}

int		func_pipe(t_ast_node *root)
{
	int pipefd[2];
	int ret;

	set_job(root);
	if (!root->piped_cmd)
		root->piped_cmd = 1;
	if (pipe(pipefd) < 0)
		return (ft_error(errno, NULL));
	ft_printf("{red}pipefd[0] = %d, pipefd[1] = %d{eoc}\n", pipefd[0], pipefd[1]);
	func_pipe_left(root, pipefd);
	ret = func_pipe_right(root, pipefd);
	if (root->piped_cmd == 1)
	{
		ft_printf("PID killed = %d, tag_gpid = %d\n", getpid(), root->tag_gpid);
		ft_printf("{red}HOW MANY WAIT ? %s %s{eoc}\n", root->left->content, root->right->content);
		ret = jc_set(root->tag_gpid, root->mod_gpid);
	}
	sh21_get()->status = ret;
	return (ret);
}
