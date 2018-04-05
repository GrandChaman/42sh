/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:01:17 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

t_lex	*shell_command2(t_lex *lex)
{
	t_lex *tmp;

	if (assert_lex((tmp = is_token(lex, While))))
		lex = tmp;
	else if (assert_lex((tmp = is_token(lex, Until))))
		lex = tmp;
	else
		return (g_err_lex);
	lex = list_root(lex);
	lex = is_token(lex, Do);
	lex = list_root(lex);
	lex = is_token(lex, Done);
	return (lex);
}

t_lex	*shell_command(t_lex *lex)
{
	t_lex *tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	if (assert_lex((tmp = for_command(lex))) ||
		assert_lex((tmp = case_command(lex))) ||
		assert_lex((tmp = select_command(lex))) ||
		assert_lex((tmp = if_command(lex))) ||
		assert_lex((tmp = subshell(lex))) ||
		assert_lex((tmp = group_command(lex))) ||
		assert_lex((tmp = function_def(lex))))
		return (tmp);
	else
		return (shell_command2(lex));
}
