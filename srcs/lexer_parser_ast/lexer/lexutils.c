/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 20:29:45 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/23 17:33:16 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh21.h"
#include "libft.h"

void		check_semi_stat(t_lexa *lexa)
{
	if (lexa->c == ';' && lexa->stat == SOP)
		lexa->stat = SNIL;
}

void		on_quote(t_lexa *lexa)
{
	int		q;

	if (lexa->oquote == 0)
	{
		lexa->t = WORD;
		lexa->oquote = lexa->c == '"' ? 1 : 2;
		lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buff_sz);
	}
	else
	{
		q = lexa->c == '"' ? 1 : 2;
		if (lexa->oquote == q)
			lexa->oquote = 0;
		lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buff_sz);
	}
}

void		on_blank(t_lexa *lexa)
{
	if (lexa->buffer && lexa->buffer[0])
	{
		if (str_digit(lexa->buffer))
			lexa->t = IO_NUM_SPC;
		add_elem_back((void**)&lexa->lex,
						(void*)lex_create(lexa->t, lexa->buffer));
		ft_strdel(&lexa->buffer);
	}
}

void		on_operator_prev(t_lexa *lexa)
{
	if (is_operator_part(lexa->c, lexa->stat))
	{
		lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buff_sz);
		lexa->t = get_operator_tok(lexa->buffer);
	}
	else
	{
		lexa->t = get_operator_tok(lexa->buffer);
		add_elem_back((void**)&lexa->lex,
					(void*)lex_create(lexa->t, lexa->buffer));
		ft_strdel(&lexa->buffer);
		lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buff_sz);
		lexa->t = WORD;
		lexa->stat = SWORD;
	}
}

void		on_operator(t_lexa *lexa)
{
	lexa->stat = SOP;
	if (lexa->buffer && lexa->buffer[0])
	{
		add_elem_back((void**)&lexa->lex,
					(void*)lex_create(lexa->t, lexa->buffer));
		ft_strdel(&lexa->buffer);
	}
	lexa->buffer = ft_strpushback(lexa->buffer, lexa->c, &g_lexa_buff_sz);
	lexa->t = get_operator_tok(lexa->buffer);
}
