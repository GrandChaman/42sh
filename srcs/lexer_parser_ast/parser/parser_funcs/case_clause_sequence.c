/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_clause_sequence.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:06:36 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*case_clause_sequence(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	lex = pattern_list(lex);
	lex = is_token(lex, DSEMI);
	while (assert_lex((tmp = pattern_list(lex))))
		lex = is_token(tmp, DSEMI);
	return (lex);
}
