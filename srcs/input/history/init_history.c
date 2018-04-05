/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:29:48 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 17:46:01 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int		check_history_line_add(t_sh21 *sh21, char *history_line,
	int line_nb)
{
	int i;

	i = 0;
	if (!*history_line)
		return (1);
	if (ft_atoi(history_line) == line_nb)
		sh21->input.history_line_nb++;
	if (!str_isprint(history_line))
	{
		ft_printf("%[RED]--History file corrupted--\n%[NC]");
		return (0);
	}
	while (ft_isdigit(history_line[i]))
		i++;
	while (history_line[i] == ' ')
		i++;
	add_elem_front_dl((void**)&sh21->input.history.list,
		add_history_list(history_line + i));
	return (1);
}

void			init_history(t_sh21 *sh21)
{
	char *history_line;

	sh21->input.history_line_nb = 1;
	history_line = NULL;
	sh21->input.history_fd = open("./doc/history", O_RDWR | O_CREAT, 0644);
	if (sh21->input.history_fd == -1)
	{
		ft_printf("%[RED]--History file corrupted--\n%[NC]");
		return ;
	}
	while (get_next_line(sh21->input.history_fd, &history_line) > 0)
	{
		if (!check_history_line_add(sh21, history_line,
			sh21->input.history_line_nb))
		{
			del_list((void**)&sh21->input.history.list, del_history);
			sh21->input.history_fd = -1;
		}
		ft_strdel(&history_line);
	}
	ft_strdel(&history_line);
}
