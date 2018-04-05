/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_list1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:04:19 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*simple_list1(t_lex *lex)
{
	if (!assert_lex(lex))
		return (g_err_lex);
	lex = pipeline_command(lex);
	if (assert_lex(lex) && (lex->token_type == AMPER
		|| lex->token_type == SEMI))
	{
		if (lex->next)
			lex = simple_list1(lex->next);
		return (lex);
	}
	else if (assert_lex(lex) && (lex->token_type == AND_IF
		|| lex->token_type == OR_IF))
	{
		lex = newline_list(lex->next);
		lex = simple_list1(lex);
		return (lex);
	}
	return (lex);
}
