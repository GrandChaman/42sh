/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_def.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:25:45 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*function_def(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	if (assert_lex((tmp = is_token(lex, WORD))))
	{
		lex = is_token(tmp, LPAREN);
		lex = is_token(lex, RPAREN);
	}
	else
	{
		lex = is_token(lex, Function);
		lex = is_token(tmp, WORD);
		if (assert_lex((tmp = is_token(lex, LPAREN))))
			lex = is_token(tmp, RPAREN);
	}
	lex = newline_list(lex);
	lex = group_command(lex);
	return (lex);
}
