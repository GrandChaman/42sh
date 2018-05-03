/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:18:35 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*if_command(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	lex = is_token(lex, If);
	lex = compound_list(lex);
	lex = is_token(lex, Then);
	lex = compound_list(lex);
	if (assert_lex((tmp = elif_clause(lex))))
		lex = tmp;
	else if (assert_lex((tmp = is_token(lex, Else))))
		lex = compound_list(tmp);
	lex = is_token(lex, Fi);
	return (lex);
}
