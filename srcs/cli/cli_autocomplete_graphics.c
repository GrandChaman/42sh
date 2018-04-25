/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete_graphics.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 16:41:32 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/19 18:21:05 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

void		cancel_autocompletion(t_ft_sh *shell, unsigned long rchar)
{
	if (shell->autocomplete && rchar != T_TAB && rchar != T_LARR &&
		rchar != T_RARR && rchar != T_ENTER)
	{
		ready_cursor_autocompletion();
		exec_term_command(TC_CLEAR_FROM_HERE);
		exec_term_command(TC_RESETCURPOS);
		if (shell->autocomplete)
			ft_lstdel(&shell->autocomplete, delete_autocomplete_entry);
		shell->autocomplete_cusor = NULL;
	}
}

static void	select_autocompletion(t_ft_autoc_entry *item, int invert_video)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	if (invert_video)
		exec_term_command(TC_REVERSEVIDEO);
	if (item->y_pos > 0)
		exec_term_command_p(TC_MOVENDOWN, 0, item->y_pos);
	if (item->x_pos > 0)
		exec_term_command_p(TC_MOVENRIGHT, 0, item->x_pos);
	if (item->undeline)
		exec_term_command(TC_UNDERLINE_ON);
	ft_printf("%s%-*s{eoc}", item->color, sh->autocomplete_padding, item->name);
	exec_term_command(TC_UNDERLINE_OFF);
	if (invert_video)
	{
		exec_term_command(TC_RESETGRAPHICS);
		exec_term_command(TC_RESETCURPOS);
	}
	else
	{
		if (item->y_pos > 0)
			exec_term_command_p(TC_MOVENUP, 0, item->y_pos);
		exec_term_command_p(TC_MOVENLEFT, 0, item->x_pos +
			sh->autocomplete_padding);
	}
}

void		move_in_autocompletion(unsigned long touch)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	ready_cursor_autocompletion();
	if (touch == T_TAB)
		touch = T_RARR;
	if (sh->autocomplete_cusor)
		select_autocompletion(sh->autocomplete_cusor->content, 0);
	if (!sh->autocomplete_cusor)
		sh->autocomplete_cusor = sh->autocomplete;
	else if (sh->autocomplete_cusor && (touch == T_LARR || touch == T_RARR))
	{
		if (touch == T_LARR && !sh->autocomplete_cusor->prev)
			while (sh->autocomplete_cusor->next)
				sh->autocomplete_cusor = sh->autocomplete_cusor->next;
		else if (touch == T_RARR && !sh->autocomplete_cusor->next)
			while (sh->autocomplete_cusor->prev)
				sh->autocomplete_cusor = sh->autocomplete_cusor->prev;
		else if (touch == T_LARR)
			sh->autocomplete_cusor = sh->autocomplete_cusor->prev;
		else if (touch == T_RARR)
			sh->autocomplete_cusor = sh->autocomplete_cusor->next;
	}
	select_autocompletion(sh->autocomplete_cusor->content, 1);
}

void		display_autocomplete(t_ft_sh *sh, t_list *list)
{
	t_ft_autoc_entry	*tmp;
	int					last_y;

	ready_cursor_autocompletion();
	last_y = 0;
	while (list)
	{
		tmp = ((t_ft_autoc_entry*)list->content);
		if (tmp->y_pos != last_y)
		{
			exec_term_command(TC_CARRIAGERETURN);
			if (last_y < tmp->y_pos)
				exec_term_command(TC_MOVEDOWN);
			else
				exec_term_command_p(TC_MOVENUP, 0, last_y - tmp->y_pos);
			last_y = tmp->y_pos;
		}
		if (tmp->undeline)
			exec_term_command(TC_UNDERLINE_ON);
		ft_printf("%s%-*s{eoc}", tmp->color, sh->autocomplete_padding,
			tmp->name);
		exec_term_command(TC_UNDERLINE_OFF);
		list = list->next;
	}
	exec_term_command(TC_RESETCURPOS);
}

void		prepare_autocomplete(t_ft_sh *sh, t_list *list,
	unsigned int save_cur)
{
	int		len;
	int		nb_per_line;
	int		nb_lines;
	int		i;

	len = ft_lstsize(list);
	nb_per_line = sh->x_size / sh->autocomplete_padding;
	nb_lines = (len / nb_per_line) + 1;
	while (sh->cursor < sh->buf.cursor)
		move_in_terminal(T_RARR);
	i = 0;
	while (i++ < nb_lines)
		ft_putchar('\n');
	exec_term_command_p(TC_MOVENUP, 0, i - 1);
	sh->cursor = sh->buf.cursor;
	exec_term_command_p(TC_MOVENRIGHT, 0, (sh->prompt_size +
		cursor_new_origin(sh)) % sh->x_size);
	while (sh->cursor > save_cur)
		move_in_terminal(T_LARR);
}
