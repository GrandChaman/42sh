/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_assignment_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:20:11 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/18 23:20:17 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_ast_node		*ast_assignment_word(t_lex **lex, t_ast_node *node)
{
	node->content = ft_strfjoin(node->content, (*lex)->content);
	node->content = ft_strfjoin(node->content, " ");
	(*lex) = (*lex)->next;
	return (node);
}
