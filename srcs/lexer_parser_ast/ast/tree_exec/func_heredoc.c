/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:56:16 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/19 17:44:20 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			func_dless(t_ast_node *root)
{
	int		out_fd;
	int		ret;

	ret = 0;
	out_fd = 0;
	if (sh21_get()->signal == T_CTRL_C)
		return (1);
	if (root->left)
		ret = g_exec_fn[root->left->type](root->left);
	ret += func_redirection(root);
	return (ret);
}
