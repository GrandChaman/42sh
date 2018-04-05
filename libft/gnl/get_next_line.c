/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:18:02 by bluff             #+#    #+#             */
/*   Updated: 2017/12/22 13:13:39 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>

static t_list		*get_element(int const fd, t_list **rt_gnl)
{
	t_list	*el;
	t_list	*tmp;
	t_gnl	*ngnl;

	tmp = *rt_gnl;
	while (tmp)
		if (((t_gnl*)tmp->content)->fd == fd)
			return (tmp);
		else
			tmp = tmp->next;
	if (!(ngnl = (t_gnl*)malloc(sizeof(t_gnl))))
		ft_perror("malloc", "Mallocation failed. Aborting");
	ngnl->fd = fd;
	ngnl->cursor = 0;
	ngnl->current_line = NULL;
	ft_bzero(ngnl->buffer, BUFF_SIZE);
	ngnl->ll = 0;
	el = ft_lstnew(ngnl, sizeof(t_gnl));
	free(ngnl);
	ft_lstadd(rt_gnl, el);
	return (el);
}

void				join_currentline(t_gnl *gnl)
{
	char *tmp;

	if (gnl->current_line)
	{
		if (!(tmp = ft_strjoin(gnl->current_line, gnl->buffer + gnl->cursor)))
			return ;
		free(gnl->current_line);
		gnl->current_line = tmp;
	}
	else
		gnl->current_line = ft_strjoin("", gnl->buffer + gnl->cursor);
}

int					extract_line(t_list *el, char **line)
{
	int		i;
	char	*tmp;
	t_gnl	*gnl;

	gnl = ((t_gnl*)el->content);
	i = 0;
	while (gnl->buffer[gnl->cursor + i] && gnl->buffer[gnl->cursor + i] != '\n')
		i++;
	if (gnl->buffer[gnl->cursor + i] == '\n')
	{
		tmp = ft_strsub(gnl->buffer, gnl->cursor, i);
		*line = ft_strjoin(gnl->current_line, tmp);
		free(tmp);
		free(gnl->current_line);
		gnl->current_line = NULL;
		gnl->cursor = (!gnl->buffer[gnl->cursor]) ? 0 : gnl->cursor + i + 1;
		if (!gnl->buffer[gnl->cursor])
			ft_bzero(gnl->buffer, BUFF_SIZE + 1);
		return (1);
	}
	join_currentline(gnl);
	gnl->cursor = 0;
	return (0);
}

void				free_el(t_gnl *cgnl, t_list **rt_gnl)
{
	t_list *el;

	el = *rt_gnl;
	while (el)
	{
		if (((t_gnl*)el->content)->fd == cgnl->fd)
		{
			if (cgnl->current_line)
				free(cgnl->current_line);
			free(el->content);
			*rt_gnl = el->next;
			free(el);
			return ;
		}
		else if (el->next && ((t_gnl*)el->next->content)->fd == cgnl->fd)
		{
			if (cgnl->current_line)
				free(cgnl->current_line);
			free(el->next->content);
			el->next = el->next->next;
			free(el->next);
			return ;
		}
		el = el->next;
	}
}

int					get_next_line(int const fd, char **line)
{
	t_list			*el;
	t_gnl			*cgnl;
	int				res;
	static t_list	*rt_gnl = NULL;

	if (fd < 0 || !line)
		return (-1);
	el = get_element(fd, &rt_gnl);
	cgnl = ((t_gnl*)el->content);
	if (extract_line(el, line))
		return (1);
	while ((res = read(fd, cgnl->buffer, BUFF_SIZE)) > 0)
	{
		cgnl->ll = 1;
		cgnl->buffer[res] = '\0';
		if (extract_line(el, line))
			return (1);
	}
	if (cgnl->ll && ft_strcmp(cgnl->current_line, ""))
		*line = ft_strdup(cgnl->current_line);
	if (cgnl->ll && ft_strcmp(cgnl->current_line, ""))
		res = 1;
	if (!res || cgnl->ll)
		free_el(cgnl, &rt_gnl);
	return (res);
}
