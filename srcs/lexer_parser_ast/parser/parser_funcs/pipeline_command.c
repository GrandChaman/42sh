/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/24 16:32:11 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*pipeline_command(t_lex *lex)
{
	t_lex *tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	if (assert_lex((tmp = is_token(lex, Bang))))
		lex = tmp;
	lex = pipeline(lex);
	return (lex);
}
