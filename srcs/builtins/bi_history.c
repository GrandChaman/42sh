/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:55:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/19 16:14:52 by fle-roy          ###   ########.fr       */
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
	while (tmp && ++i)
	{
		entry = (t_ft_hist_entry*)tmp->content;
		ft_bzero(t_format, 50);
		strftime(t_format, 50, "%e/%d/%G %H:%M:%S",
			localtime((const time_t *)&entry->timestamp));
		ft_printf("%d\t%s\t%s\n", i - 1, t_format, entry->command);
		tmp = tmp->prev;
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
	if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
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

static int	find_history_divergence(char *path, char **line, t_list **hist, int *fd)
{
	t_ft_sh		*sh;
	char		*tmp;
	int			gnl_res;

	sh = get_ft_shell();
	if (!sh->history)
		return (-1);
	*hist = ft_lstlast(sh->history);
	if ((*fd = open(path, O_RDWR)) < 0)
		return (ft_fprintf(2, "42sh: history: can't write to "
		"file %s.\n", path) * -1);
	while (*hist && (gnl_res = get_next_line(*fd, line)) > 0)
	{
		tmp = ft_strchr(*line, ' ');
		if (!tmp)
			continue ;
		++tmp;
		if (!ft_strcmp(tmp, ((t_ft_hist_entry*)(*hist)->content)->command))
			*hist = (*hist)->prev;
		else
			break ;
		ft_strdel(line);
	}
	return (gnl_res);
}

static int			append_new_line_to_hist_file(char *path)
{
	int		fd;
	char	*line;
	int		gnl_res;
	t_list	*tmp;

	line = NULL;
	gnl_res = find_history_divergence("toto.txt", &line, &tmp, &fd);
	free(line);
	if (gnl_res < 0)
		return ((close(fd) + ft_fprintf(2,
			"42sh: history: Error while reading history file %s\n")) || 1);
	if (lseek(fd, 0, SEEK_END) < 0)
		return ((close(fd) + ft_fprintf(2, "42sh: history: lseek() failed\n"))
			&& 1);
	while (tmp)
	{
		ft_fprintf(fd, "%lu %s\n",
			((t_ft_hist_entry*)tmp->content)->timestamp,
			((t_ft_hist_entry*)tmp->content)->command);
		tmp = tmp->prev;
	}
	close(fd);
	return (0);
}

static int			append_new_line_to_hist(char *path)
{
	int		fd;
	char	*line;
	int		gnl_res;
	t_list	*tmp;
	t_ft_sh	*sh;

	sh = get_ft_shell();
	gnl_res = find_history_divergence("toto.txt", &line, &tmp, &fd);
	if (gnl_res < 0)
		return ((close(fd) + ft_fprintf(2,
			"42sh: history: Error while reading history file %s\n")) || 1);
	if (line)
		parse_and_add_to_history(sh, line);
	free(line);
	read_history(get_ft_shell(), fd);
	if (lseek(fd, 0, SEEK_END) < 0)
		return ((close(fd) +
			ft_fprintf(2, "42sh: history: lseek() failed\n")) || 1);
	close(fd);
	return (0);
}

static int			delete_at_offset(int offset)
{
	t_ft_sh	*sh;
	t_list	*tmp;

	sh = get_ft_shell();
	if (sh->history_size >= SH_HIST_MAX_SIZE)
		offset--;
	if (offset < 0 || sh->history_size - offset < 0)
		return (ft_fprintf(2, "42sh: history: %d: index out of range\n",
			offset) && 1);
	if (!(tmp = ft_lstat(sh->history, sh->history_size - offset - 1)))
		return (1);
	ft_lstdelone(&tmp, delete_hist_entry);
	sh->history_size--;
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
		return (flags.err);
	if (flags.d)
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
	if (flags.c)
		ret = 0;
	if (flags.awrn == 'r')
		ret = 0;
	return (ret);
}
