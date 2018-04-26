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

static char		*exec_subshell_routine(t_sh21 *sh21, char *str,
	int nerr_subsh, int nw_subsh)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		del_sh21();
		sh21->lex = lexer(str);
		if (parser(sh21->lex))
			sh21->status = exec_tree(sh21->tree.root_node);
		del_sh21_exit();
		exit(sh21->status);
	}
	else
	{
		wait(&pid);
		dup2(nerr_subsh, 2);
		dup2(nw_subsh, 1);
	}
	return (str);
}

char			*exec_subshell(char *str, char *file_nm_io)
{
	t_sh21	*sh21;
	int		res_fd_subsh;
	int		nw_subsh;
	int		nerr_subsh;

	sh21 = sh21_get();
	res_fd_subsh = open(file_nm_io, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	nw_subsh = dup(1);
	nerr_subsh = dup(2);
	dup2(res_fd_subsh, 1);
	close(2);
	return (exec_subshell_routine(sh21, str, nerr_subsh, nw_subsh));
}
