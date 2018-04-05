/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:03:47 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*pipeline(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	if (assert_lex((tmp = command(lex))))
	{
		lex = tmp;
		if (assert_lex((tmp = is_token(lex, PIPE))))
		{
			lex = tmp;
			lex = newline_list(lex);
			lex = pipeline(lex);
			return (lex);
		}
		return (lex);
	}
	else
		return (g_err_lex);
}
