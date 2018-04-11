/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_nav.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:55:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/19 13:28:39 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

unsigned int	cursor_new_origin(t_ft_sh *sh)
{
	unsigned int i;
	unsigned int res;

	res = sh->cursor;
	i = 1;
	while ((int)(sh->buf.cursor - i) > 0)
	{
		if (sh->buf.buf[sh->buf.cursor - i] == '\n')
		{
			res = i - 1;
			break ;
		}
		i++;
	}
	return (res);
}

int				is_last_char_a_nl(void)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	return (sh->cursor > 0 && sh->buf.buf[sh->cursor - 1] == '\n');
}

int				is_alt_shell_begin(void)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	return (sh->cursor > 0 && sh->buf.buf[sh->cursor - 1] == '\n' &&
		sh->is_alt_shell);
}

void			nav_touch_received(unsigned long touch)
{
	if ((touch & SHIFT_MASK) == SHIFT_MASK)
		skip_in_terminal(touch);
	else if (touch == T_HOME || touch == T_END ||
		touch == T_CTRL_A || touch == T_CTRL_E)
		home_or_end_touch(touch);
	else if (get_ft_shell()->autocomplete)
		move_in_autocompletion(touch);
	else
		move_in_terminal(touch);
}

void			move_in_terminal(unsigned long touch)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	if (touch == T_LARR && sh->cursor > 0 && !is_last_char_a_nl())
	{
		if (sh->is_a_tty && ((sh->prompt_size +
			(sh->cursor - sh->alt_cursor)) % (sh->x_size)) == 0)
		{
			exec_term_command(TC_MOVEUP);
			exec_term_command_p(TC_MOVENRIGHT, 0, sh->x_size - 1);
		}
		else if (sh->is_a_tty)
			exec_term_command(TC_MOVELEFT);
		sh->cursor -= 1;
	}
	else if (touch == T_RARR && sh->cursor < sh->buf.cursor)
	{
		if (sh->is_a_tty && ((sh->prompt_size +
			(sh->cursor - sh->alt_cursor)) % (sh->x_size)) == sh->x_size - 1)
			ft_putchar('\n');
		else if (sh->is_a_tty)
			exec_term_command(TC_MOVERIGHT);
		sh->cursor += 1;
	}
}
