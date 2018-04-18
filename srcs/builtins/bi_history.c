/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:55:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/18 16:02:47 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "cli.h"
#include <time.h>

static int			display_history(int lim)
{
	t_ft_sh			*sh;
	t_list			*tmp;
	t_ft_hist_entry	*entry;
	unsigned int	i;
	char			t_format[50];

	sh = get_ft_shell();
	i = 0;
	if (lim < 0 || lim > sh->history_size)
		return (ft_fprintf(2, "42sh: history: %d: index out of range\n", lim)
			&& 1);
	if (!(tmp = (lim ? ft_lstat(sh->history, lim) : ft_lstlast(sh->history))))
		return (0);
	if (tmp != sh->history)
		i = sh->history_size;
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

static int			clear_history(void)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	ft_lstdel(&sh->history, delete_hist_entry);
	sh->history_size = 0;
	return (0);
}

static int			read_and_append_history_form_file(char *path)
{
	t_ft_sh		*sh;
	int			fd;

	sh = get_ft_shell();
	if ((fd = open(path, O_RDONLY)) < 0)
		return (ft_fprintf(2, "42sh: history: can't read file %s.\n", path)
			&& 1);
	if (read_history(sh, fd) < 0)
	{
		close(fd);
		return (ft_fprintf(2, "42sh: history: error while reading %s.\n", path)
			&& 1);
	}
	close(fd);
}

static int			write_history_to_file(char *path)
{
	t_ft_sh		*sh;
	int			fd;

	sh = get_ft_shell();
	if ((fd = open(path, O_WRONLY)) < 0)
		return (ft_fprintf(2, "42sh: history: can't write to file %s.\n", path)
			&& 1);
	write_history(sh, fd, 0);
	close(fd);
	return (0);
}

static int			delete_at_offset(int offset)
{
	t_ft_sh	*sh;
	int		len;
	t_list	*tmp;

	sh = get_ft_shell();
	len = sh->history_size;
	if (offset < 0 || len - offset < 0)
		return (ft_fprintf(2, "42sh: history: %d: index out of range\n",
			offset) && 1);
	if (!(tmp = ft_lstat(sh->history, len - offset)))
		return (1);
	ft_lstdelone(&tmp, delete_hist_entry);
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
		return (0);//Handle param
	else
	{
		while (argv[1][i])
			if (!ft_isdigit(argv[1][i++]))
				return (ft_fprintf(2, "42sh: history: %s: numeric argument"
					" required\n", argv[1]) && 1);
		return (display_history(ft_atoi(argv[1])));
	}

}
