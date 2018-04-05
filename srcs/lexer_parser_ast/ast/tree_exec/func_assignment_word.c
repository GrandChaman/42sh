/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_assignment_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/15 16:39:39 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"

int		func_assignment_word(t_ast_node *root)
{
	t_sh21	*sh21;
	int		ret;

	ret = 0;
	if (root->left && root->left->left)
		ret = g_exec_fn[root->left->left->type](root->left->left);
	sh21 = sh21_get();
	root->content = format_word(&root->content);
	ret += ft_putenv(ft_strdup(root->content), &sh21->env.local_var);
	return (ret);
}
