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

int		func_pipe2(t_ast_node *root, int pipefd[2])
{
	int		nw;
	int		status;
	int		ret;

	status = 0;
	close(pipefd[1]);
	if (root->right)
	{
		root->right->pipe_fd[0] = pipefd[0];
		root->right->piped_cmd = 1;
		status = g_exec_fn[root->right->type](root->right);
	}
	del_sh21_exit();
	exit(status);
}

int		func_pipe(t_ast_node *root)
{
	int pipefd[2];
	int pid;
	int ret_child;
	int ret;

	// set_job(root);
	ret_child = 0;
	if (pipe(pipefd) < 0)
		return (ft_error(errno, NULL));
	pid = fork();
	if (pid == 0)
		func_pipe2(root, pipefd);
	else
	{
		close(pipefd[0]);
		root->left->piped_cmd = 1;
		root->left->pipe_fd[0] = root->pipe_fd[0];
		root->left->pipe_fd[1] = pipefd[1];
		ret_child = g_exec_fn[root->left->type](root->left);
	}
	// ret = jc_set(root->tag_gpid, root->mod_gpid);
	waitpid(pid, &ret, WUNTRACED);
	sh21_get()->status = ret;
	return (ret);
}
