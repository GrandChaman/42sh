/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:06:21 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*compound_list(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	if (lex->token_type == EOI)
		return (lex);
	if (assert_lex((tmp = list_root(lex))))
		return (tmp);
	else
	{
		lex = newline_list(lex);
		lex = list1(lex);
		return (lex);
	}
}
