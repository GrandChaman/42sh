/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:55:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/24 16:19:25 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "cli.h"
#include <time.h>

static int			display_history(int limit)
{
	t_ft_sh			*sh;
	t_list			*tmp;
	t_ft_hist_entry	*entry;
	unsigned int	i;
	char			t_format[50];

	sh = get_ft_shell();
	i = 0;
	if (!(tmp = (limit || limit > ft_lstsize(sh->history) ?
		ft_lstat(sh->history, limit) : ft_lstlast(sh->history))))
		return (0);
	if (tmp != sh->history)
		i = ft_lstsize(tmp);
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

int					bi_history(int argc, char **argv, char ***environ)
{
	int i;

	i = 0;
	(void)environ;
	if (argc == 1)
		return (display_history(0));
	if (argv[1][0] == '-')
		return (0);
	else
	{
		while (argv[1][i])
			if (!ft_isdigit(argv[1][i++]))
				return (ft_fprintf(2, "history: %s: numeric argument"\
" required", argv[1]) && 1);
		return (display_history(ft_atoi(argv[1])));
	}
}
