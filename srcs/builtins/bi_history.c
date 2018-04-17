/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:55:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/17 18:20:08 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "cli.h"
#include <time.h>

int					bi_history(int argc, char **argv, char ***environ)
{
	t_ft_sh			*sh;
	t_list			*tmp;
	t_ft_hist_entry	*entry;
	unsigned int	i;
	char			t_format[50];

	(void)argc;
	(void)argv;
	(void)environ;
	sh = get_ft_shell();
	tmp = sh->history;
	tmp = ft_lstlast(tmp);
	if (!tmp)
		return (0);
	i = 0;
	while ((tmp = tmp->prev))
	{
		entry = (t_ft_hist_entry*)tmp->content;
		ft_bzero(t_format, 50);
		strftime(t_format, 50, "%e/%d/%G %H:%M:%S",
			localtime((const time_t *)&entry->timestamp));
		ft_printf("%d\t%s\t%s\n", i, t_format, entry->command);
		i++;
	}
	return (0);
}
