/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:56:29 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/26 14:47:22 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh21.h"
#include "libft.h"

void		check_eval(t_lexa *lexa)
{
	if (ends_with(lexa->buffer, "$(("))
		lexa->in_eval = 1;
	if (ends_with(lexa->buffer, "))"))
		lexa->in_eval = 0;
}

int		lex_1(t_lexa *lexa)
{
	if (lexa->c == '`')
	{
		on_subshell(lexa);
		return (1);
	}
	else if (lexa->c == '"' || lexa->c == '\'')
	{
		on_quote(lexa);
		return (1);
	}
	else if (lexa->oquote)
	{
		lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buf);
		return (1);
	}
	else if (lexa->c == ' ')
	{
		on_blank(lexa);
		return (1);
	}
	return (0);
}

int		lex_2(t_lexa *lexa)
{
	if (is_operator_part(lexa->prev, lexa->stat))
	{
		lexa->escaped ? lexfallbackesc(lexa) : on_operator_prev(lexa);
		return (1);
	}
	else if (is_operator_part(lexa->c, lexa->stat))
	{
		on_operator(lexa);
		return (1);
	}
	else if (lexa->stat == SWORD)
	{
		on_word(lexa);
		return (1);
	}
	return (0);
}

t_lex			*lexer(char *cmd)
{
	t_lexa		lexa;

	lexa.in_eval = 0;
	lexa.cmd = cmd;
	lexa_init(&lexa, cmd);
	while (*lexa.str && (lexa.c = *(lexa.str)))
	{
		check_semi_stat(&lexa);
		check_eval(&lexa);
		if (lexa.c == '\\')
			escape(&lexa);
		else if (lexa.in_eval)
		{
			if (!ft_iswhitespace(lexa.c))
				lexa.buffer = ft_strpushback(lexa.buffer, lexa.c, &g_lexa_buf);
		}
		else if (lex_1(&lexa))
			;
		else if (lex_2(&lexa))
			;
		else
			lexfallback(&lexa);
		lexa.prev = lexa.c;
		++(lexa.str);
	}
	return (end_lex(&lexa));
}
