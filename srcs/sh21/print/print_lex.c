/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:55:11 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/16 13:49:08 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	print_lex_list(t_lex *elem)
{
	t_sh21 *sh21;

	sh21 = sh21_get();
	ft_fprintf(sh21->debug_tty, "\n\n==============================\n");
	while (elem)
	{
		ft_fprintf(sh21->debug_tty, "Tok: %-16s '{red}%s{eoc}(%i) SHLVL = %s\n",
				g_token_type_str[(int)elem->token_type], elem->content,
				elem->token_type, ft_getenv("SHLVL", &sh21->env.orig_env));
		elem = elem->next;
	}
}
