/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/24 16:26:29 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"

int		func_word(t_ast_node *root)
{
	t_sh21			*sh21;
	char			*cmd;

	cmd = NULL;
	sh21 = sh21_get();
	if (!root || sh21->signal == T_CTRL_C)
		return (!root ? 0 : 1);
	cmd = ft_strdup(root->content);
	cmd = format_word(&cmd, root);
	root->argv = split_args(cmd, root);
	set_job(root);
	sh21->status = sh21_exec(root->argv, &sh21->env.orig_env, root);
	del_arr(&root->argv);
	ft_strdel(&cmd);
	return (sh21->status);
}
