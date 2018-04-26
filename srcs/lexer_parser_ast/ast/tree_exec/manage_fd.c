/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:51:36 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/26 14:51:38 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		change_fd(t_ast_node *root)
{
	int ret;

	ret = 1;
	if (root->piped_cmd)
	{
		if (root->pipe_to_close > 2)
			close(root->pipe_to_close);
		if (root->pipe_fd[0] != 0)
			if ((root->tmp_fd_read = dup(0)) < 0
				|| dup2(root->pipe_fd[0], 0) < 0)
				ret = 0;
		if (ret && root->pipe_fd[1] != 1)
			if ((root->tmp_fd_write = dup(1)) < 0
				|| dup2(root->pipe_fd[1], 1) < 0)
				ret = 0;
		if (!ret)
			return (ft_error(errno, "pipe"));
	}
	if (ret && root->redir_node)
		ret = g_exec_fn[root->redir_node->type](root->redir_node);
	return (ret);
}

int		reset_fd(t_ast_node *root)
{
	if (root->piped_cmd)
	{
		if (root->pipe_fd[0] != 0)
			close(root->pipe_fd[0]);
		if (root->pipe_fd[1] != 1)
			close(root->pipe_fd[1]);
	}
	return (0);
}
