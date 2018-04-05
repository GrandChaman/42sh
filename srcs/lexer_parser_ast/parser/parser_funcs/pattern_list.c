/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:06:45 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*pattern_list(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	lex = newline_list(lex);
	if (assert_lex((tmp = is_token(lex, LPAREN))))
		lex = tmp;
	lex = is_token(lex, WORD);
	while (assert_lex(tmp = is_token(lex, PIPE)))
		lex = is_token(tmp, WORD);
	lex = is_token(lex, RPAREN);
	if (assert_lex((tmp = compound_list(lex))))
		return (tmp);
	else
	{
		lex = newline_list(lex);
		return (lex);
	}
}
