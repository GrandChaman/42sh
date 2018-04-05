/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:27:05 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 15:59:50 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_fd_cleanup	*create_fd_cleanup(t_fd_function fd_function,
				int fd_close, int fd_reassign)
{
	t_fd_cleanup *ret;

	ret = (t_fd_cleanup*)malloc(sizeof(t_fd_cleanup));
	if (ret == NULL)
	{
		ft_error(errno, NULL);
		return (NULL);
	}
	ret->fd_function = fd_function;
	ret->fd_close = fd_close;
	ret->fd_reassign = fd_reassign;
	ret->next = NULL;
	return (ret);
}

void			fd_close(t_fd_cleanup *elem)
{
	close(elem->fd_close);
}

void			fd_reassign(t_fd_cleanup *elem)
{
	if (dup2(elem->fd_close, elem->fd_reassign) == -1)
		ft_error(errno, NULL);
	if (close(elem->fd_close) == -1)
		ft_error(errno, NULL);
}
