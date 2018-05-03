/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:20:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/18 23:20:52 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_ast_node		*ast_word(t_lex **lex, t_ast_node *node)
{
	node->type = WORD;
	if (node->content)
		node->content = ft_strfjoin(node->content, " ");
	node->content = ft_strfjoin(node->content, (*lex)->content);
	(*lex) = (*lex)->next;
	return (node);
}
