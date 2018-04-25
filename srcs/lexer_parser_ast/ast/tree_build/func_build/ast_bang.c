/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_bang.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:20:31 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/24 19:17:53 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_ast_node		*ast_bang(t_lex **lex, t_ast_node *node)
{
	if (!lex || !*lex || !(*lex)->next)
		return (NULL);
	node->type = (*lex)->token_type;
	*lex = (*lex)->next;
	node->left = ast_create_leaf((*lex)->token_type, lex);
	return (node);
}
