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
