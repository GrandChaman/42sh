/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:31:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 18:01:22 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_lex	*redirection3(t_lex *lex)
{
	t_lex *tmp;

	if (assert_lex((tmp = is_token(lex, DLESSDASH))))
		return (is_token(tmp, IO_NUMBER));
	else if (assert_lex((tmp = is_token(lex, ANDGREAT))))
		return (is_token(tmp, WORD));
	else if (assert_lex((tmp = is_token(lex, LESSGREAT))))
		return (is_token(tmp, WORD));
	else if (assert_lex((tmp = is_token(lex, CLOBBER))))
		return (is_token(tmp, WORD));
	else if (assert_lex((tmp = is_token(lex, IO_NUMBER))))
		return (redirection(tmp));
	else
		return (g_err_lex);
}

t_lex	*redirection2(t_lex *lex)
{
	t_lex *tmp;

	if (assert_lex((tmp = is_token(lex, LESSAND))))
	{
		lex = tmp;
		if (assert_lex((tmp = is_token(lex, IO_NUMBER))) ||
			assert_lex((tmp = is_token(lex, WORD))))
			return (tmp);
		return (g_err_lex);
	}
	else if (assert_lex((tmp = is_token(lex, GREATAND))))
	{
		lex = tmp;
		if (assert_lex((tmp = is_token(lex, IO_NUMBER))) ||
			assert_lex((tmp = is_token(lex, WORD))))
			return (tmp);
		return (g_err_lex);
	}
	else
		return (redirection3(lex));
}

t_lex	*redirection(t_lex *lex)
{
	t_lex	*tmp;

	if (!assert_lex(lex))
		return (g_err_lex);
	DEBUG(lex);
	if (assert_lex((tmp = is_token(lex, GREATANDDASH))))
		return (tmp);
	else if (assert_lex((tmp = is_token(lex, ANDGREATDASH))))
		return (tmp);
	else if (assert_lex((tmp = is_token(lex, LESSANDDASH))))
		return (tmp);
	else if (assert_lex((tmp = is_token(lex, GREATER))))
		return (is_token(tmp, WORD));
	else if (assert_lex((tmp = is_token(lex, LESS))))
		return (is_token(tmp, WORD));
	else if (assert_lex((tmp = is_token(lex, DGREAT))))
		return (is_token(tmp, WORD));
	else if (assert_lex((tmp = is_token(lex, DLESS))))
		return (is_token(tmp, WORD));
	else
		return (redirection2(lex));
}
