/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:07:38 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/26 14:48:53 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static char		*exec_subshell_routine(t_sh21 *sh21, char *str, int file_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		sh21_get()->tty = dup(1);
		close(2);
		dup2(file_fd, 1);
		del_sh21();
		sh21->lex = lexer(str);
		if (parser(sh21->lex))
			sh21->status = exec_tree(sh21->tree.root_node);
		del_sh21_exit();
		exit(sh21->status);
	}
	else
		waitpid(pid, &status, 0);
	close (file_fd);
	return (str);
}

char			*exec_subshell(char *str, char *file_nm_io)
{
	t_sh21	*sh21;
	int		res_fd_subsh;

	sh21 = sh21_get();
	res_fd_subsh = open(file_nm_io, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	return (exec_subshell_routine(sh21, str, res_fd_subsh));
}
