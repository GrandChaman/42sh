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
	int				status;
	char			*cmd;

	status = 0;
	cmd = NULL;
	sh21 = sh21_get();
	if (!root)
		return (0);
	if (sh21->signal == T_CTRL_C)
		return (1);
	cmd = ft_strdup(root->content);
	cmd = format_word(&cmd, root);
	root->argv = split_args(cmd, root);
	set_job(root);
	if (!status)
		status = sh21_exec(root->argv, &sh21->env.orig_env, root); //add tag_gpid
	sh21->status = status;
	del_arr(&root->argv);
	ft_strdel(&cmd);
	return (status);
}
