/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:56:29 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/22 16:16:56 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh21.h"
#include "libft.h"
// modif
t_lex		*lex_create(t_token_type token_type, char *content)
{
	t_lex	*lex;

	lex = ft_memalloc(sizeof(t_lex));
	if (content)
		lex->content = ft_strdup(content);
	else
	{
		lex->content = ft_memalloc(sizeof(char) * 1);
		lex->content[0] = '\0';
	}
	lex->token_type = token_type;
	lex->next = NULL;
	return (lex);
}

static int	end_lex(t_lexa *lexa, t_sh21 *sh21)
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
	sh21->lex = lexa->lex;
	return (1);
}

static void	escape(t_lexa *lexa)
{
	lexa->stat = SWORD;
	lexa->t = WORD;
	lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buff_sz);
	lexa->c = *++(lexa->str);
	lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buff_sz);
}

static void	lexfallbackesc(t_lexa *lexa)
{
	lexa->stat = SWORD;
	lexa->t = WORD;
	lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buff_sz);
}

int			lexer(t_sh21 *sh21)
{
	t_lexa		lexa;

	lexa_init(&lexa, sh21);
	while (*lexa.str && (lexa.c = *(lexa.str)))
	{
		check_semi_stat(&lexa);
		if (lexa.c == '\\')
			escape(&lexa);
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
	return (end_lex(&lexa, sh21));
}
