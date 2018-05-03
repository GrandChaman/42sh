/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:04:27 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*simple_list(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	lex = simple_list1(lex);
	if (assert_lex((tmp = is_token(lex, AMPER))))
		return (tmp);
	else if (assert_lex((tmp = is_token(lex, SEMI))))
		return (tmp);
	return (lex);
}
