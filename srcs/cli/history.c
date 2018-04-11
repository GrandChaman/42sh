/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 10:48:18 by bluff             #+#    #+#             */
/*   Updated: 2018/03/22 13:53:58 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

char			*search_history_nav(t_ft_sh *sh, char *search, int up)
{
	t_list	*list;
	int		slen;
	int		clen;
	int		pos_save;

	pos_save = sh->history_pos;
	slen = ft_strlen(search);
	clen = ft_strlen(sh->buf.buf);
	list = (sh->history_pos >= 0 && sh->history_pos < sh->history_size ?
		ft_lstat(sh->history, sh->history_pos) : sh->history);
	sh->history_pos = (sh->history_pos < 0 && up ? 0 : sh->history_pos);
	while (list)
	{
		if (!ft_strncmp(search, ((t_ft_hist_entry*)list->content)->command,
			slen) && (int)ft_strlen(
				((t_ft_hist_entry*)list->content)->command) != clen)
			return (((t_ft_hist_entry*)list->content)->command);
		sh->history_pos += (up ? 1 : -1);
		list = (up ? list->next : list->prev);
	}
	sh->history_pos = pos_save;
	if (!up)
		sh->history_pos = -1;
	return (NULL);
}

void			replace_command(char *newcommand)
{
	t_ft_sh	*sh;
	size_t	len;

	sh = get_ft_shell();
	while (sh->cursor < sh->buf.cursor)
		move_in_terminal(T_RARR);
	while (sh->cursor > 0)
		backspace_command(0);
	dbuf_clear(&sh->buf);
	if (!newcommand)
		return ;
	len = ft_strlen(newcommand);
	dbuf_append(&sh->buf, newcommand);
	write(1, newcommand, len);
	sh->cursor = sh->buf.cursor;
	if (sh->is_a_tty && ((sh->prompt_size +
		(sh->cursor - sh->alt_cursor)) % (sh->x_size)) == 0)
		ft_putchar('\n');
}

char			*normal_history_nav(t_ft_sh *sh, int up)
{
	if (!up && sh->history_pos <= 0)
	{
		while (sh->cursor < sh->buf.cursor)
			move_in_terminal(T_RARR);
		while (sh->cursor > 0)
			backspace_command(0);
		sh->history_pos = -1;
		return (NULL);
	}
	else if (up && sh->history_pos >= sh->history_size - 1)
		return (((t_ft_hist_entry*)ft_lstat(sh->history,
			sh->history_size - 1)->content)->command);
	else
		return (((t_ft_hist_entry*)ft_lstat(sh->history, (up ?
			++sh->history_pos : --sh->history_pos))->content)->command);
}

static void		history_nav_routine(unsigned long touch, t_ft_sh *sh, char *tmp)
{
	if (sh->history_pos >= sh->history_size || ft_strcmp(sh->buf.buf,
		((t_ft_hist_entry*)ft_lstat(sh->history,
			sh->history_pos)->content)->command))
	{
		ft_free((void**)&sh->history_last);
		sh->history_pos = -1;
	}
	if ((!sh->history_last && sh->history_pos >= 0) || (!sh->buf.buf[0]
		&& sh->history_pos < 0))
		tmp = normal_history_nav(sh, (touch == T_TARR ? 1 : 0));
	else
	{
		if (!sh->history_last)
			sh->history_last = ft_strdup(sh->buf.buf);
		tmp = search_history_nav(sh, sh->history_last,
			(touch == T_TARR ? 1 : 0));
	}
	if (sh->history_pos >= 0 && tmp)
		replace_command(tmp);
	else if (sh->history_pos < 0 && !tmp)
	{
		replace_command(sh->history_last);
		ft_free((void**)&sh->history_last);
	}
}

void			history_nav(unsigned long touch)
{
	t_ft_sh *sh;
	char	*tmp;

	sh = get_ft_shell();
	tmp = NULL;
	if (!sh->history || sh->is_alt_shell)
		return ;
	history_nav_routine(touch, sh, tmp);
}
