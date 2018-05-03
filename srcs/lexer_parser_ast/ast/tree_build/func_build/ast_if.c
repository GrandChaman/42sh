/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_if.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:20:31 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/24 19:15:48 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_ast_node		*ast_else(t_lex **lex, t_ast_node *root)
{
	t_ast_node			*node;

	(void)root;
	if (!lex || !*lex || !(*lex)->next)
		return (NULL);
	node = ast_create_node((*lex)->token_type, NULL);
	*lex = (*lex)->next;
	node->left = ast_compound_list(lex, node);
	return (node);
}

t_ast_node		*ast_elif(t_lex **lex, t_ast_node *root)
{
	t_ast_node			*node;

	(void)root;
	if (!lex || !*lex || !(*lex)->next)
		return (NULL);
	node = ast_create_node((*lex)->token_type, NULL);
	*lex = (*lex)->next;
	node->condition_node = ast_compound_list(lex, node);
	*lex = (*lex)->next;
	node->left = ast_compound_list(lex, node);
	if ((*lex)->token_type == Elif)
		node->right = ast_elif(lex, node);
	else if ((*lex)->token_type == Else)
		node->right = ast_else(lex, node);
	return (node);
}

t_ast_node		*ast_if(t_lex **lex, t_ast_node *node)
{
	if (!lex || !*lex || !(*lex)->next)
		return (NULL);
	node->type = (*lex)->token_type;
	*lex = (*lex)->next;
	node->condition_node = ast_compound_list(lex, node);
	*lex = (*lex)->next;
	node->left = ast_compound_list(lex, node);
	if ((*lex)->token_type == Elif)
		node->right = ast_elif(lex, node);
	else
		node->right = ast_else(lex, node);
	*lex = (*lex)->next;
	while ((*lex) && ast_redir_node((*lex)->token_type))
		node->redir_node = redir_node(lex, node->redir_node);
	return (node);
}
