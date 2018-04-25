/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/24 19:15:24 by hfontain         ###   ########.fr       */
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
	node->content = NULL;
	node->heredoc = NULL;
	node->left = NULL;
	node->right = NULL;
	node->redir_node = NULL;
	node->assign_node = NULL;
	node->condition_node = NULL;
	node->tag_gpid = -1;
	node->mod_gpid = FG;
	node->piped_cmd = 0;
	node->pipe_fd[0] = 0;
	node->pipe_to_close = -1;
	node->nb_escaped_quote = 0;
	node->i = 0;
	node->quote_count = 0;
	node->type = type;
	if ((node->pipe_fd[1] = 1) && str)
		node->content = ft_strdup(str);
	return (node);
}

static t_ast_node	*(*g_ast_pipeline_cmd_token[])(t_lex **, t_ast_node *) =
{NULL, ast_word, ast_assignment_word, ast_pipe,
	ast_while, ast_if, ast_until, ast_bang};

t_ast_node		*ast_create_leaf(t_token_type type, t_lex **lex)
{
	t_ast_node		*node;
	int				call_fc;

	if (!lex || !*lex)
		return (NULL);
	node = ast_create_node(type, NULL);
	while (*lex && ((call_fc = ast_is_shell_cmd((*lex)->token_type))
	|| ast_redir_node((*lex)->token_type)))
	{
		if (ast_redir_node((*lex)->token_type))
			node->redir_node = redir_node(lex, node->redir_node);
		else
			node = g_ast_pipeline_cmd_token[call_fc](lex, node);
	}
	return (node);
}

t_ast_node		*ast_create_op(t_ast_node *node, t_lex **lex)
{
	t_ast_node	*root;

	root = ast_create_node((*lex)->token_type, (*lex)->content);
	root->left = node;
	*lex = (*lex)->next;
	if (*lex && ((*lex)->token_type == WORD))
		root->right = ast_create_leaf((*lex)->token_type, lex);
	return (root);
}

t_ast_node		*ast_create_tree(t_lex *lex)
{
	t_ast_node	*node;

	node = ast_create_leaf(lex->token_type, &lex);
	while (lex)
		node = ast_create_op(node, &lex);
	return (node);
}
