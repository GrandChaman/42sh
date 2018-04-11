/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 11:07:06 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/03 16:29:02 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

static int		ft_putchar_tty(int c)
{
	write(1, &c, 1);
	return (0);
}

void			exec_term_command(const char *code)
{
	tputs(tgoto(tgetstr((char*)code, NULL), 0, 1), 1, ft_putchar_tty);
}

void			exec_term_command_p(const char *code, int p1, int p2)
{
	tputs(tgoto(tgetstr((char*)code, NULL), p1, p2), 1, ft_putchar_tty);
}
