/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history_io.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 17:08:33 by fle-roy           #+#    #+#             */
/*   Updated: 2018/05/04 16:17:09 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "cli.h"

int			hist_divergence(char *path, char **line, t_list **hist, int *fd)
{
	t_ft_sh		*sh;
	char		*tmp;
	int			gnl_res;

	sh = get_ft_shell();
	if (!sh->history)
		return (-1);
	if (!(path = (path ? ft_strdup(path) : get_history_file())))
		return (hist_error("42sh: history: can't open default history file."
			" HOME not defined ", "", -1));
		*hist = ft_lstlast(sh->history);
	if ((*fd = open(path, O_RDWR)) < 0)
		return (hist_error("42sh: history: can't write to file ", path, -1));
	while (*hist && (gnl_res = get_next_line(*fd, line)) > 0)
	{
		if (!(tmp = ft_strchr(*line, ' ')))
			continue ;
		if (!ft_strcmp(++tmp, ((t_ft_hist_entry*)(*hist)->content)->command))
			*hist = (*hist)->prev;
		else
			break ;
		ft_strdel(line);
	}
	free(path);
	return (gnl_res);
}

int			hist_sync_file(char *path)
{
	int		fd;
	char	*line;
	int		gnl_res;
	t_list	*tmp;

	line = NULL;
	if (!(path = (path ? ft_strdup(path) : get_history_file())))
		return (hist_error("42sh: history: can't open default history file."
			" HOME not defined ", "", -1));
		gnl_res = hist_divergence(path, &line, &tmp, &fd);
	free(line);
	if (gnl_res < 0)
		return (hist_error("42sh: history: Error while"
		" reading history file ", path, fd));
		if (lseek(fd, 0, SEEK_END) < 0)
		return (hist_error("42sh: history: lseek() failed : ", path, fd));
	while (tmp)
	{
		ft_fprintf(fd, "%lu %s\n", ((t_ft_hist_entry*)tmp->content)->timestamp,
			((t_ft_hist_entry*)tmp->content)->command);
		tmp = tmp->prev;
	}
	close(fd);
	free(path);
	return (0);
}

int			hist_sync(char *path)
{
	int		fd;
	char	*line;
	int		gnl_res;
	t_list	*tmp;
	t_ft_sh	*sh;

	sh = get_ft_shell();
	path = (path ? ft_strdup(path) : get_history_file());
	if (!path)
		return (hist_error("42sh: history: can't open default history file."
			" HOME not defined ", "", -1));
		gnl_res = hist_divergence(path, &line, &tmp, &fd);
	if (gnl_res < 0)
		return (hist_error("42sh: history: Error while reading"
		" history file ", path, fd));
		if (line)
		parse_and_add_to_history(sh, line);
	free(line);
	read_history(get_ft_shell(), fd);
	if (lseek(fd, 0, SEEK_END) < 0)
		return (hist_error("42sh: history: lseek() failed : ", path, fd));
		close(fd);
	ft_strdel(&path);
	free(path);
	return (0);
}

int			hist_append_file(char *path)
{
	t_ft_sh		*sh;
	int			fd;

	sh = get_ft_shell();
	path = (path ? ft_strdup(path) : get_history_file());
	if (!path)
		return (hist_error("42sh: history: can't open default history file."
			" HOME not defined ", "", -1));
		if ((fd = open(path, O_RDONLY)) < 0)
		return (hist_error("42sh: history: can't read file ", path, -1));
		if (read_history(sh, fd) < 0)
			return (hist_error("42sh: history: error while reading ", path,
				fd));
	close(fd);
	ft_strdel(&path);
	free(path);
	return (0);
}

int			hist_write(char *path)
{
	t_ft_sh		*sh;
	int			fd;

	sh = get_ft_shell();
	path = (path ? ft_strdup(path) : get_history_file());
	if (!path)
		return (hist_error("42sh: history: can't open default history file."
			" HOME not defined ", "", -1));
		if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
			return (hist_error("42sh: history: can't write to file ", path,
				-1));
		write_history(sh, fd, 0);
	close(fd);
	ft_strdel(&path);
	free(path);
	return (0);
}
