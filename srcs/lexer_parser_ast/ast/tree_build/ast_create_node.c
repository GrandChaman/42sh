/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/12 18:08:18 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh21.h"

t_ast_node		*ast_create_node(t_token_type type, char *str)
{
	t_ast_node	*node;

	if (!(node = malloc(sizeof(t_ast_node))))
		ft_exit(errno, NULL);
	if (!node)
		return (NULL);
	node->type = type;
	if (str)
		node->content = ft_strdup(str);
	else
		node->content = NULL;
	node->left = NULL;
	node->right = NULL;
	node->heredoc = NULL;
	return (node);
}

t_ast_node		*ast_pipe(t_token_type type, t_lex **lex, t_ast_node *root)
{
	t_ast_node *node;

	if (!lex || !*lex)
		return (NULL);
	node = ast_create_node(type, (*lex)->content);
	*lex = (*lex)->next;
	node->left = root;
	node->right = ast_create_leaf((*lex)->token_type, lex);
	return (node);
}

t_ast_node		*ast_create_leaf(t_token_type type, t_lex **lex)
{
	t_ast_node	*node;
	int			i;

	i = 0;
	if (!lex || !*lex)
		return (NULL);
	node = ast_create_node(type, NULL);
	while (*lex && ((*lex)->token_type == WORD ||
		ast_redir_token((*lex)->token_type)
		|| (i > 1 && (*lex)->token_type == EQUAL)))
	{
		if ((*lex)->token_type == PIPE)
			node = ast_pipe((*lex)->token_type, lex, node);
		else if (ast_redir_token((*lex)->token_type))
			node->left = redir_node(lex, node->left);
		else
		{
			node->content = ft_strfjoin(node->content, (*lex)->content);
			node->content = ft_strfjoin(node->content, " ");
			(*lex) = (*lex)->next;
		}
		i++;
	}
	return (node);
}

t_ast_node		*ast_create_op(t_ast_node *node, t_lex **lex)
{
	t_ast_node *root;

	root = ast_create_node((*lex)->token_type, (*lex)->content);
	root->left = node;
	*lex = (*lex)->next;
	if (*lex && ((*lex)->token_type == WORD))
		root->right = ast_create_leaf((*lex)->token_type, lex);
	return (root);
}

t_ast_node		*ast_create_tree(t_lex *lex)
{
	t_ast_node *node;

	node = ast_create_leaf(lex->token_type, &lex);
	while (lex)
		node = ast_create_op(node, &lex);
	return (node);
}
