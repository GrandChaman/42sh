/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_element.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:01:12 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*simple_command_element(t_lex *lex)
{
	t_lex *tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	if (assert_lex((tmp = is_token(lex, WORD))) ||
		assert_lex((tmp = is_token(lex, ASSIGNMENT_WORD))))
	{
		lex = tmp;
		if (assert_lex((tmp = is_token(lex, EQUAL))))
		{
			lex = tmp;
			if (assert_lex((tmp = is_token(lex, WORD))))
				return (tmp);
			else
				return (g_err_lex);
		}
		else
			return (lex);
	}
	else if (assert_lex((tmp = redirection(lex))))
	{
		return (tmp);
	}
	else
		return (g_err_lex);
}
