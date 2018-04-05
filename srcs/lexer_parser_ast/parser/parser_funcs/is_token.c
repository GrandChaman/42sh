/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/15 16:01:48 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*is_token(t_lex *lex, t_token_type token_type)
{
	if (!assert_lex(lex))
		return (g_err_lex);
	if (lex && ((lex->token_type == token_type)))
	{
		if (!lex->next)
		{
			return (g_end_of_input);
		}
		return (lex->next);
	}
	else
	{
		ft_strdel(&g_err_lex->content);
		if (lex->token_type != WORD)
			g_err_lex->content = ft_strdup(g_token_type_str[lex->token_type]);
		else
		{
			g_err_lex->content = ft_strdup(lex->content);
		}
		return (g_err_lex);
	}
}
