/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:55:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/19 14:22:53 by hfontain         ###   ########.fr       */
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
	if (lim)
		i = sh->history_size - lim;
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
	return (0);
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

static int			display_cmd(int argc, const char **argv, int should_display)
{
	int i;

	i = -1;
	if (!should_display)
		return (0);
	while (++i < argc)
		ft_printf("%s\n", argv);
	return (0);
}

static char	*find_diverging_point_in_history_file(char *path, int *fd)
{
	t_ft_sh		*sh;
	char		*line;
	char		*tmp;
	t_list		*hist;

	sh = get_ft_shell();
	if (!sh->history)
		return (NULL);
	hist = ft_lstlast(sh->history);
	if ((*fd = open(path, O_WRONLY)) < 0)
		return ((void*)(long)(ft_fprintf(2, "42sh: history: can't write to "
		"file %s.\n", path) && 0));
	while (hist && get_next_line(*fd, &line) > 0)
	{
		tmp = ft_strchr(line, ' ');
		if (!tmp)
			continue ;
		if (!ft_strcmp(tmp, ((t_ft_hist_entry*)hist->content)->command))
			hist = hist->prev;
		else
			break ;
		free(line);
	}
	return (line);
	// return ((t_ft_hist_entry){.command = ft_strdup(tmp),
	// 	.timestamp = ft_atoi(line)})
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
	ft_printf("Deleting : %s\n", ((t_ft_hist_entry*)(tmp->content))->command);
	ft_lstdelone(&tmp, delete_hist_entry);
	return (0);
}

int					bi_history(int argc, char **argv, char ***environ)
{
	int ret;
	t_hist_args flags;

	(void)environ;
	ret = 0;
	if (argc == 1)
		return (display_history(0));
	read_args(&flags, argc, argv);
	if (flags.err)
		return (flags.err); // Handle err here
	if (flags.d == 'd')
		return (display_history(flags.d_val));
	if (flags.p)
		ret = 0; //-p
	if (flags.s)
		ret = 0; //-s
	if (flags.awrn == 'a')
		ret = 0;
	else if (flags.awrn == 'w')
		ret = 0;
	else if (flags.awrn == 'n')
		ret = 0;
	if (flags.awrn == 'r')
		ret = 0;
	if (flags.c)
		ret = 0;
	return (ret);
}
