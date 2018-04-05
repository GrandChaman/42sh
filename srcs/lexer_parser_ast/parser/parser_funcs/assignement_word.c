/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:08:49 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*assignment_word(t_lex *lex)
{
	if (!assert_lex(lex))
		return (g_err_lex);
	lex = is_token(lex, WORD);
	lex = is_token(lex, EQUAL);
	lex = is_token(lex, WORD);
	return (lex);
}
