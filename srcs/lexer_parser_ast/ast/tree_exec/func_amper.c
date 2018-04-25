/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:59:29 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/15 15:59:35 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh21.h"

int		func_amper(t_ast_node *root)
{
	int ret;

	ret = 0;
	if (root->left && (root->left->type == SEMI || root->left->type == AND_IF
		|| root->left->type == OR_IF))
	{
		if (root->left->right)
			root->left->right->mod_gpid = BG;
	}
	else if (root->left)
		root->left->mod_gpid = BG;
	if (root->left)
		ret = g_exec_fn[root->left->type](root->left);
	if (root->right)
		ret = g_exec_fn[root->right->type](root->right);
	return (ret);
}
