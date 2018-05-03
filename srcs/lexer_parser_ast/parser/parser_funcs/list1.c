/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:14:16 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*list1(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	lex = pipeline_command(lex);
	tmp = lex;
	while (tmp->token_type == AMPER || tmp->token_type == SEMI ||
		tmp->token_type == AND_IF || tmp->token_type == OR_IF ||
		tmp->token_type == NEWLINE)
	{
		tmp = tmp->next;
		tmp = newline_list(tmp);
		tmp = pipeline_command(tmp);
		if (assert_lex(tmp))
			lex = tmp;
	}
	return (lex);
}
