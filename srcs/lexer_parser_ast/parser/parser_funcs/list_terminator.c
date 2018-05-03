/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_terminator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:03:05 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/12 18:05:02 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*list_terminator(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	if (assert_lex((tmp = is_token(lex, NEWLINE))))
		return (tmp);
	else if (assert_lex((tmp = is_token(lex, SEMI))))
		return (tmp);
	else
		return (g_err_lex);
}
