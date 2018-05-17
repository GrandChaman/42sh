/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_while.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:20:39 by fbertoia          #+#    #+#             */
/*   Updated: 2018/05/11 16:00:52 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_ast_node		*ast_while(t_lex **lex, t_ast_node *node)
{
	if (!lex || !*lex || !(*lex)->next)
		return (NULL);
	node->type = (*lex)->token_type;
	*lex = *lex ? (*lex)->next : *lex;
	node->left = ast_compound_list(lex, node);
	*lex = *lex ? (*lex)->next : *lex;
	node->right = ast_compound_list(lex, node);
	if (lex && *lex)
		*lex = (*lex)->next;
	while (*lex && ast_redir_node((*lex)->token_type))
		node->redir_node = redir_node(lex, node->redir_node);
	return (node);
}
