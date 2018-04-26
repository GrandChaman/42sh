/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_selection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 11:18:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/26 16:59:48 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

void		cancel_selection(t_ft_sh *shell, unsigned long rchar)
{
	unsigned int	i;
	int				cur_save;

	i = shell->cursor + 1;
	if (rchar != T_ALT_C && rchar != T_ALT_V && rchar != T_ALT_X &&
		rchar != T_ALT_LEFT && rchar != T_ALT_RIGHT && shell->select_size)
	{
		exec_term_command(TC_SAVECURPOS);
		cur_save = shell->cursor;
		while (i-- > 0)
			move_in_terminal(T_LARR);
		update_stdout(shell, 0);
		shell->select_start = 0;
		shell->select_size = 0;
		exec_term_command(TC_RESETCURPOS);
		shell->cursor = cur_save;
	}
	if (!shell->select_size)
		shell->select_start = 0;
}

#include "sh21.h"

void		move_select(unsigned long touch)
{
	t_ft_sh *sh;
	int		tmp;

	sh = get_ft_shell();
	if (((sh->cursor == 0 || is_alt_shell_begin()) && touch == T_ALT_LEFT)
		|| (sh->cursor == sh->buf.cursor && touch == T_ALT_RIGHT))
		return ;
	if (!sh->select_size)
		sh->select_start = sh->cursor;
	tmp = sh->select_size + (touch == T_ALT_LEFT ? -1 : 1);
	if (sh->select_start + tmp - 1 != sh->cursor)
		move_in_terminal((touch == T_ALT_LEFT ? T_LARR : T_RARR));
	if (ABS(tmp) > ABS(sh->select_size))
		exec_term_command(TC_REVERSEVIDEO);
	ft_putchar(sh->buf.buf[sh->cursor]);
	exec_term_command(TC_MOVELEFT);
	if (sh->is_a_tty && ((sh->prompt_size + (sh->cursor - sh->alt_cursor)) %
		(sh->x_size)) == sh->x_size - 1)
		exec_term_command(TC_MOVERIGHT);
	if (sh->select_start + tmp - 1 == sh->cursor)
		move_in_terminal(T_RARR);
	exec_term_command(TC_RESETGRAPHICS);
	sh->select_size += (touch == T_ALT_LEFT ? -1 : 1);
}

void		copy_select(unsigned long touch)
{
	t_ft_sh	*sh;

	(void)touch;
	sh = get_ft_shell();
	ft_strdel(&sh->select);
	if (sh->select_size < 0)
		sh->select = ft_strsub(sh->buf.buf, sh->select_start + sh->select_size,
			sh->select_size * -1);
	else
		sh->select = ft_strsub(sh->buf.buf, sh->select_start, sh->select_size);
}

void		paste_select(unsigned long touch)
{
	t_ft_sh	*sh;
	int		i;
	int		len;

	(void)touch;
	sh = get_ft_shell();
	len = ft_strlen(sh->select);
	if (!len)
		return ;
	i = 0;
	while (i < len)
	{
		dbuf_insert(&sh->buf, sh->cursor + i, sh->select[i]);
		i++;
	}
	update_stdout(sh, 0);
	while (--i > 0)
		move_in_terminal(T_RARR);
	cancel_selection(sh, 0);
}

void		cut_select(unsigned long touch)
{
	t_ft_sh	*sh;
	int		len;
	int		tmp;

	(void)touch;
	sh = get_ft_shell();
	ft_strdel(&sh->select);
	if (sh->select_size < 0)
		sh->select = ft_strsub(sh->buf.buf, sh->select_start + sh->select_size,
			sh->select_size * -1);
	else
		sh->select = ft_strsub(sh->buf.buf, sh->select_start, sh->select_size);
	len = ft_strlen(sh->select);
	tmp = len;
	while (len-- > 0)
		if (sh->select_size > 0)
			backspace_command(T_BACKSPACE);
		else
			delete_command(T_DELETE);
	sh->select_start = 0;
	sh->select_size = 0;
}
