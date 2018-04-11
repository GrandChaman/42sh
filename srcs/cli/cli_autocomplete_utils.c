/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 16:48:51 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/19 13:13:37 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

int				cmp_autoc_entry(void *e1, void *e2)
{
	return (ft_strcmp(((t_ft_autoc_entry*)e1)->name,
		((t_ft_autoc_entry*)e2)->name));
}

int				get_autocomplete_el_with(t_list *list)
{
	int res;
	int tmp;

	res = 0;
	while (list)
	{
		tmp = ft_strlen(((t_ft_autoc_entry*)list->content)->name);
		if (res < tmp)
			res = tmp;
		list = list->next;
	}
	return (res);
}

void			delete_autocomplete_entry(void *el, size_t size)
{
	(void)size;
	ft_free((void**)&((t_ft_autoc_entry*)el)->name);
	ft_free(&el);
}

void			ready_cursor_autocompletion(void)
{
	unsigned int	cur_save;
	t_ft_sh			*sh;

	sh = get_ft_shell();
	cur_save = sh->cursor;
	exec_term_command(TC_SAVECURPOS);
	while (sh->cursor < sh->buf.cursor)
		move_in_terminal(T_RARR);
	ft_putchar('\n');
	sh->cursor = cur_save;
}

void			setpos_autocomplete(t_ft_sh *sh)
{
	unsigned int	x;
	unsigned int	y;
	t_list			*list;

	list = sh->autocomplete;
	x = 0;
	y = 0;
	while (list)
	{
		((t_ft_autoc_entry*)list->content)->x_pos = x *
			sh->autocomplete_padding;
		((t_ft_autoc_entry*)list->content)->y_pos = y;
		if ((x + 2) * sh->autocomplete_padding > sh->x_size)
		{
			x = 0;
			y++;
		}
		else
			x++;
		list = list->next;
	}
}
