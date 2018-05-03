/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:01:05 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*subshell(t_lex *lex)
{
	if (!assert_lex(lex))
		return (g_err_lex);
	lex = is_token(lex, LPAREN);
	lex = compound_list(lex);
	lex = is_token(lex, RPAREN);
	return (lex);
}
