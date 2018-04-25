/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_while.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:20:39 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/18 23:20:41 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_ast_node		*ast_while(t_lex **lex, t_ast_node *node)
{
	if (!lex || !*lex || !(*lex)->next)
		return (NULL);
	node->type = (*lex)->token_type;
	*lex = (*lex)->next;
	node->left = ast_compound_list(lex, node);
	(*lex) = (*lex)->next;
	node->right = ast_compound_list(lex, node);
	(*lex) = (*lex)->next;
	while ((*lex) && ast_redir_node((*lex)->token_type))
		node->redir_node = redir_node(lex, node->left);
	return (node);
}
