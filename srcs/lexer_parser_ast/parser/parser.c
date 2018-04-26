/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:56:29 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/25 18:45:56 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh21.h"

int		parser(t_lex *lex)
{
	t_lex	*cpy;

	cpy = lex;
	if (size_list(lex) == 1 && lex->token_type == EOI)
		return (0);
	lex = program(lex);
	if (lex && lex->token_type == EOI)
	{
		sh21_get()->tree.root_node = ast_create_tree(cpy);
		return (1);
	}
	ft_fprintf(2, "{red}42sh{eoc}: Syntax error near '%s'\n", lex->content);
	ft_strdel(&g_err_lex->content);
	return (0);
}
