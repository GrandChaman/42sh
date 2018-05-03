/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_clause.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:06:59 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*case_clause(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	if (assert_lex((tmp = case_clause_sequence(lex))))
		lex = tmp;
	lex = pattern_list(lex);
	return (lex);
}
