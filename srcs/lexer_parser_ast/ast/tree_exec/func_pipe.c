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
	nw = dup(0);
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	if (root->right)
		ret = g_exec_fn[root->right->type](root->right);
	wait(&status);
	dup2(nw, 0);
	close(nw);
	exit(0);
}

int		func_pipe(t_ast_node *root)
{
	int pipefd[2];
	int pid;
	int ret_child;
	int nw;
	int ret;

	ret_child = 0;
	if (pipe(pipefd) < -1)
		return (ft_error(errno, NULL));
	pid = fork();
	if (pid == 0)
		func_pipe2(root, pipefd);
	else
	{
		nw = dup(1);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		ret_child = g_exec_fn[root->left->type](root->left);
		dup2(nw, 1);
		close(nw);
	}
	waitpid(pid, &ret, WUNTRACED);
	sh21_get()->status = ret;
	return (ret);
}
