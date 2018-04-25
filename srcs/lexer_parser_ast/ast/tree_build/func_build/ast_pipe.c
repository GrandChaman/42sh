/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:20:34 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/18 23:20:38 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_ast_node		*ast_pipe(t_lex **lex, t_ast_node *root)
{
	t_ast_node *node;

	if (!lex || !*lex)
		return (NULL);
	node = ast_create_node((*lex)->token_type, (*lex)->content);
	*lex = (*lex)->next;
	node->left = root;
	node->right = ast_create_leaf((*lex)->token_type, lex);
	return (node);
}
