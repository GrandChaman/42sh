/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:48:34 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/16 14:41:13 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"

int				ast_redir_node(t_token_type type)
{
	if (type == IO_NUMBER
		|| type == GREATER
		|| type == DGREAT
		|| type == ANDGREAT
		|| type == GREATAND
		|| type == ANDGREATDASH
		|| type == GREATANDDASH
		|| type == LESS
		|| type == LESSAND
		|| type == LESSANDDASH
		|| type == DLESS
		|| type == DLESSDASH
		|| type == CLOBBER
		|| type == GREATAND)
		return (1);
	return (0);
}

t_ast_node		*redir_node(t_lex **lex, t_ast_node *node)
{
	t_ast_node		*ret;
	t_token_type	tmp;

	ret = ast_create_node((*lex)->token_type, NULL);
	if ((*lex)->token_type == IO_NUMBER)
	{
		ret->left = ast_create_node(IO_NUMBER, (*lex)->content);
		*lex = (*lex)->next;
	}
	ret->content = ft_strdup((*lex)->content);
	ret->type = (*lex)->token_type;
	tmp = (*lex)->token_type;
	*lex = (*lex)->next;
	if (ret->left)
		ret->left->left = node;
	else
		ret->left = node;
	if (tmp == GREATANDDASH || tmp == LESSANDDASH || tmp == ANDGREATDASH)
		return (ret);
	ret->right = ast_create_node((*lex)->token_type, (*lex)->content);
	*lex = (*lex)->next;
	if (tmp == DLESS || tmp == DLESSDASH)
		heredoc_node(ret->right);
	return (ret);
}
