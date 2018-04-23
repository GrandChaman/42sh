/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/06 17:27:58 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"

int		func_word(t_ast_node *root)
{
	t_sh21			*sh21;
	int				status;

	status = 0;
	if (!root)
		return (0);
	sh21 = sh21_get();
	root->content = format_word(&root->content);
	sh21->argv = split_args(root->content);
	set_job(root);
	if (!status)
		status = sh21_exec(sh21->argv, &sh21->env.orig_env, root); //add tag_gpid
	sh21->status = status;
	del_arr(&sh21->argv);
	return (status);
}
