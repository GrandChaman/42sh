/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/02/28 18:11:33 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void			ast_free_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type != WORD)
	{
		if (node->left)
			ast_free_node(node->left);
		if (node->right)
			ast_free_node(node->right);
	}
	ft_memdel((void**)&node);
}

void			ast_free_one_node(t_ast_node *node)
{
	if (!node)
		return ;
	ft_memdel((void**)&node);
}
