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

int		assign_var(t_ast_node *node)
{
	int 		ret;
	t_assign_ls *ls;
	char		**argv;

	ls = node->assign_node;
	ret = 0;
	argv = NULL;
    while (ls)
    {
		ls->assignation = format_word(&ls->assignation, node);
		argv = split_args(ls->assignation, node);
		ret += ft_putenv(ft_strdup(argv[0]), &sh21_get()->env.local_var);
		del_arr(&argv);
        ls = ls->next;
    }
	return (ret);
}

int		func_assignment_word(t_ast_node *root)
{
	int		ret;

	ret = 0;
	if (root->left && root->left->left)
		ret = g_exec_fn[root->left->left->type](root->left->left);
	ret += assign_var(root);
	return (ret);
}
