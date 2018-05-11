/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_compound_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:20:22 by fbertoia          #+#    #+#             */
/*   Updated: 2018/05/11 15:11:28 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int				is_compound_token(t_token_type type)
{
	if (type == SEMI || type == AMPER || type == AND_IF || type == OR_IF)
		return (1);
	return (0);
}

t_ast_node		*ast_compound_list(t_lex **lex, t_ast_node *node)
{
	node = ast_create_leaf((*lex)->token_type, lex);
	while (lex && *lex && is_compound_token((*lex)->token_type))
		node = ast_create_op(node, lex);
	return (node);
}
