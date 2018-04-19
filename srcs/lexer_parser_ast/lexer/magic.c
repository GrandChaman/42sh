/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:07:38 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/19 15:11:47 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh21.h"
#include "libft.h"

static int	g_open = 0;

void	on_magicq(t_lexa *lexa)
{
	if (g_open == 0)
	{
		g_open = 1;
		g_shell_idx++;
	}
	else
	{
		g_open = 0;
		g_shell_idx--;
	}
	(void)lexa;
}
