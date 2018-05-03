/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21_exec_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:34:27 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/26 17:34:28 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		sh21_exec_builtin_no_fork(char **av, char ***env,
				t_ast_node *root, t_builtin builtin)
{
	int status;

	jc_delete_tag(root->tag_gpid);
	change_fd_or_exit(root);
	status = builtin.fn_ptr(arrlen(av), av, env, root);
	reset_fd(root);
	return (status);
}
