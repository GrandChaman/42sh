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

t_assign_ls		*create_assign_ls(t_lex **lex)
{
	t_assign_ls *ret;

	ret = (t_assign_ls*)malloc(sizeof(t_assign_ls));
	if (!ret)
		ft_exit(errno, "malloc");
	ret->next = NULL;
	ret->assignation = ft_strdup((*lex)->content);
	return (ret);
}

t_ast_node		*ast_assignment_word(t_lex **lex, t_ast_node *node)
{
	if (!lex || !*lex)
		return (NULL);
	add_elem_back((void**)&node->assign_node, (void*)create_assign_ls(lex));
	(*lex) = (*lex)->next;
	if (!node->content)
		node->type = ASSIGNMENT_WORD;
	return (node);
}
