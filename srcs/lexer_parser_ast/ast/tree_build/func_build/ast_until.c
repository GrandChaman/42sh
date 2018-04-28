/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_until.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:20:39 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/24 18:14:45 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_ast_node		*ast_until(t_lex **lex, t_ast_node *node)
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
		node->redir_node = redir_node(lex, node->redir_node);
	return (node);
}
