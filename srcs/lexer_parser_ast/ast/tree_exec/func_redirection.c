/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:27:38 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/19 12:43:40 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int			func_redirection4(t_ast_node *node, int fd[5])
{
	int err;

	err = 0;
	if (node->type == ANDGREAT || node->type == ANDGREATDASH)
	{
		fd[in_fd2] = 2;
		if ((fd[tmp_fd2] = dup(fd[in_fd2])) < 0)
		{
			ft_error(errno, node->right->content);
			err = errno;
		}
		if (!err)
			add_elem_front((void**)&sh21_get()->tree.fd_cleanup,
				create_fd_cleanup(fd_close, fd[tmp_fd2], 0));
		if (!err && dup2(fd[out_fd], fd[in_fd2]) < 0)
		{
			ft_error(errno, node->right->content);
			err = errno;
		}
		if (!err)
			add_elem_front((void**)&sh21_get()->tree.fd_cleanup,
				create_fd_cleanup(fd_reassign, fd[tmp_fd2], fd[in_fd2]));
	}
	return (err);
}

static int			func_redirection3(t_ast_node *node, int fd[5])
{
	int err;

	err = 0;
	if ((fd[tmp_fd] = dup(fd[in_fd])) < 0)
	{
		ft_error(errno, node->right->content);
		err = errno;
	}
	if (!err)
		add_elem_front((void**)&sh21_get()->tree.fd_cleanup,
			create_fd_cleanup(fd_close, fd[tmp_fd], 0));
	if (!err && dup2(fd[out_fd], fd[in_fd]) < 0)
	{
		ft_error(errno, node->right->content);
		err = errno;
	}
	if (!err)
		add_elem_front((void**)&sh21_get()->tree.fd_cleanup,
			create_fd_cleanup(fd_reassign, fd[tmp_fd], fd[in_fd]));
	if (err)
		return (err);
	return (func_redirection4(node, fd));
}

static int			func_redirection2(t_ast_node *node, int fd[5])
{
	if (node->type == LESS || node->type == LESSAND || node->type == DLESS)
	{
		if ((fd[out_fd] = open(node->right->content, O_RDONLY)) < 0)
			return (ft_error(errno, node->right->content));
		add_elem_front((void**)&sh21_get()->tree.fd_cleanup,
			create_fd_cleanup(fd_close, fd[out_fd], 0));
	}
	else if ((fd[out_fd] = open(node->right->content, (node->type ==
		LESSGREAT ? O_RDWR : O_WRONLY) | O_CREAT
		| (node->type == DGREAT ? O_APPEND : O_TRUNC), 0644)) < 0)
	{
		return (ft_error(errno, node->right->content));
	}
	else
		add_elem_front((void**)&sh21_get()->tree.fd_cleanup,
			create_fd_cleanup(fd_close, fd[out_fd], 0));
	return (0);
}

static void			handle_format_word(t_ast_node *node)
{
	char *tmp;

	if (node->left)
	{
		node->left->content = format_word(node->left->content, node->left);
		tmp = node->left->content;
		node->left->content = word(&node->left->content);
		ft_strdel(&tmp);
	}
	if (node->right)
	{
		node->right->content = format_word(node->right->content, node->right);
		tmp = node->right->content;
		node->right->content = word(&node->right->content);
		ft_strdel(&tmp);
	}
}

int					func_redirection(t_ast_node *node)
{
	int fd[5];
	int ret;

	handle_format_word(node);
	if (node->left && (ret = g_exec_fn[node->left->type](node->left)))
		return (ret);
	if (node->left && node->left->type == IO_NUMBER)
		fd[in_fd] = ft_atoi(node->left->content);
	else
		fd[in_fd] = node->type == LESS || node->type == LESSAND
		|| node->type == LESSANDDASH || node->type == DLESS ? 0 : 1;
	fd[out_fd] = node->right && node->right->type == IO_NUMBER
		? ft_atoi(node->right->content) : -1;
	if (fd[out_fd] == -1)
	{
		if (node->type == GREATANDDASH || node->type == ANDGREATDASH
			|| node->type == LESSANDDASH)
		{
			if ((fd[out_fd] = open("/dev/null", O_WRONLY)) < 0)
				return (ft_error(errno, "/dev/null"));
		}
		else if (func_redirection2(node, fd))
			return (errno);
	}
	return (func_redirection3(node, fd));
}
