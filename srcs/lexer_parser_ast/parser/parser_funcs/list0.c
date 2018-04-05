/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:03:06 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/12 18:13:09 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*list0(t_lex *lex)
{
	if (!assert_lex(lex))
		return (g_err_lex);
	lex = list1(lex);
	if (lex->token_type == NEWLINE || lex->token_type == AMPER)
		lex = lex->next;
	else
		lex = is_token(lex, SEMI);
	lex = newline_list(lex);
	return (lex);
}
