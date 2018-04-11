/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_spe_nav.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:06:28 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/19 13:16:28 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

void			vertical_nav(unsigned long touch)
{
	unsigned int	i;
	t_ft_sh			*sh;

	sh = get_ft_shell();
	i = 0;
	while (i++ < sh->x_size)
		move_in_terminal((touch == T_ALT_UP ? T_LARR : T_RARR));
}

void			skip_in_terminal(unsigned long touch)
{
	t_ft_sh		*sh;
	int			dir;
	int			tmp;

	dir = ((touch == T_SLARR ? -1 : 1));
	if (touch == T_SBARR || touch == T_STARR ||
		(touch == T_SLARR && is_last_char_a_nl()))
		return ;
	sh = get_ft_shell();
	while (sh->cursor + (dir > 0) > 0
		&& (int)sh->cursor < sh->buf.cursor + (dir < 0))
	{
		move_in_terminal((dir < 0 ? T_LARR : T_RARR));
		tmp = ((int)(sh->cursor - 1) < 0 ? 0 : sh->cursor - 1);
		if (ft_iswhitespace(sh->buf.buf[tmp]) &&
			!ft_iswhitespace(sh->buf.buf[sh->cursor]))
			break ;
	}
}

void			home_or_end_touch(unsigned long touch)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	while (((touch == T_HOME || touch == T_CTRL_A) && sh->cursor
		&& !is_last_char_a_nl()) || ((touch == T_END || touch == T_CTRL_E)
		&& sh->cursor < sh->buf.cursor))
		move_in_terminal((touch == T_HOME || touch == T_CTRL_A
			? T_LARR : T_RARR));
}
