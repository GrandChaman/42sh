/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:56:29 by hfontain          #+#    #+#             */
/*   Updated: 2018/05/03 01:05:41 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh21.h"
#include "libft.h"

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

t_lex		*end_lex(t_lexa *lexa)
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
	// ft_printf("=======lexa.str = %s========\n", lexa->buffer);
	lexa->buffer ? ft_strdel(&lexa->buffer) : (0);
	return (lexa->lex);
}

void		escape(t_lexa *lexa)
{
	lexa->stat = SWORD;
	lexa->t = WORD;
	lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buf);
	lexa->c = *++(lexa->str);
	lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buf);
}

void		lexfallbackesc(t_lexa *lexa)
{
	lexa->stat = SWORD;
	lexa->t = WORD;
	lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buf);
}

int			ends_with(char *str, char *t)
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
