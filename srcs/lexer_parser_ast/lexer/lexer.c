/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:56:29 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/25 18:33:26 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh21.h"
#include "libft.h"

static t_lex	*end_lex(t_lexa *lexa)
{
	int		prev_word;
	t_lex	*ptr;

	prev_word = 0;
	if (lexa->buffer)
		add_elem_back((void**)&lexa->lex,
			(void*)lex_create(lexa->t, lexa->buffer));
	word_recog(lexa);
	ptr = lexa->lex;
	while (ptr)
	{
		if (ptr->token_type == WORD)
		{
			if (prev_word == 0 && ft_strchr(ptr->content, '=') != NULL)
				ptr->token_type = ASSIGNMENT_WORD;
			else
				prev_word = 1;
		}
		else
			prev_word = 0;
		ptr = ptr->next;
	}
	lexa->buffer ? ft_strdel(&lexa->buffer) : (0);
	return (lexa->lex);
}

static void		escape(t_lexa *lexa)
{
	lexa->stat = SWORD;
	lexa->t = WORD;
	lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buff_sz);
	lexa->c = *++(lexa->str);
	lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buff_sz);
}

static void		lexfallbackesc(t_lexa *lexa)
{
	lexa->stat = SWORD;
	lexa->t = WORD;
	lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buff_sz);
}

int		ends_with(char *str, char *t)
{
	const int		strlen = ft_strlen(str);
	const int		tlen = ft_strlen(t);
	if (!str)
		return (0);
	if (!t)
		return (1);

	if (strlen >= tlen && ft_strcmp(str + strlen - tlen, t) == 0)
		return (1);
	return (0);
}

t_lex			*lexer(char *cmd)
{
	t_lexa		lexa;
	int			in_eval;

	in_eval = 0;
	lexa.cmd = cmd;
	lexa_init(&lexa, cmd);
	while (*lexa.str && (lexa.c = *(lexa.str)))
	{
		check_semi_stat(&lexa);
		if (ends_with(lexa.buffer, "$(("))
			in_eval = 1;
		if (ends_with(lexa.buffer, "))"))
			in_eval = 0;
		if (lexa.c == '\\')
			escape(&lexa);
		else if (in_eval)
		{
			if (!ft_iswhitespace(lexa.c))
				lexa.buffer = ft_strpushback(lexa.buffer, lexa.c, &g_lexa_buff_sz);
		}
		else if (lexa.c == '`')
			on_subshell(&lexa);
		else if (lexa.c == '"' || lexa.c == '\'')
			on_quote(&lexa);
		else if (lexa.oquote)
			lexa.buffer = ft_strpushback(lexa.buffer, lexa.c, &g_lexa_buff_sz);
		else if (lexa.c == ' ')
			on_blank(&lexa);
		else if (is_operator_part(lexa.prev, lexa.stat))
			lexa.escaped ? lexfallbackesc(&lexa) : on_operator_prev(&lexa);
		else if (is_operator_part(lexa.c, lexa.stat))
			on_operator(&lexa);
		else if (lexa.stat == SWORD)
			on_word(&lexa);
		else
			lexfallback(&lexa);
		lexa.prev = lexa.c;
		++(lexa.str);
	}
	return (end_lex(&lexa));
}
