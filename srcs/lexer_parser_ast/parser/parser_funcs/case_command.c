/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:00:58 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*case_command(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	lex = is_token(lex, Case);
	lex = is_token(lex, WORD);
	lex = newline_list(lex);
	lex = is_token(lex, In);
	if (assert_lex((tmp = case_clause(lex))))
		lex = tmp;
	else if (assert_lex((tmp = case_clause_sequence(lex))))
		lex = newline_list(tmp);
	else if (assert_lex((tmp = newline_list(lex))))
		lex = tmp;
	lex = is_token(lex, Esac);
	return (lex);
}
