/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_recognize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:49:23 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/23 17:17:53 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"

int				is_redir_part(char c)
{
	return (c == '>' || c == '<');
}

int				is_redir_token(t_token_type token_type)
{
	if (token_type == CLOBBER
	|| token_type == GREATAND
	|| token_type == LESSAND)
		return (1);
	return (0);
}

int				is_operator_part(char c, int stat)
{
	return (c == '\n'
		|| c == '&'
		|| c == '|'
		|| c == '<'
		|| c == '>'
		|| c == ';'
		|| c == '\n'
		|| c == '}'
		|| (c == '{' && stat != SWORD)
		|| (c == '=' && stat != SWORD)
		|| (stat == SOP && c == '-'));
}

t_token_type	get_operator_tok(char *str)
{
	int					i;
	const char			*str_to_compare[] = {">&-", "<&-", "&>-", "<<-",
	";;", ">|", "&&", "||", ">>", "<<", ">&", "<&", "&>", ";\n", "<", ">", "|",
	"&", ";", "=", "\n", "{", "}", "(", ")", ""};
	const t_token_type	type[] = {GREATANDDASH, LESSANDDASH,
	ANDGREATDASH, DLESSDASH, DSEMI, CLOBBER, AND_IF, OR_IF, DGREAT, DLESS,
	GREATAND, LESSAND, ANDGREAT, SEMI, LESS, GREATER, PIPE, AMPER, SEMI, EQUAL,
	SEMI, Lbrace, Rbrace, LPAREN, RPAREN, NOT_AN_OP};

	i = 0;
	while (str_to_compare[i][0] && !ft_strequ(str_to_compare[i], str))
		i++;
	return (type[i]);
}
