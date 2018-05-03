/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:09:23 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*for_command2(t_lex *lex)
{
	t_lex *tmp;

	lex = newline_list(lex);
	if (assert_lex((tmp = is_token(lex, Do))))
	{
		lex = tmp;
		lex = list_root(lex);
		lex = is_token(lex, Done);
	}
	else
	{
		lex = is_token(lex, Lbrace);
		lex = list_root(lex);
		lex = is_token(lex, Rbrace);
	}
	return (lex);
}

t_lex	*for_command(t_lex *lex)
{
	t_lex *tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	lex = is_token(lex, For);
	lex = is_token(lex, WORD);
	if (assert_lex((tmp = is_token(lex, SEMI))))
		lex = tmp;
	else
	{
		lex = newline_list(lex);
		lex = is_token(lex, In);
		lex = word_list(lex);
		lex = list_terminator(lex);
	}
	return (for_command2(lex));
}
