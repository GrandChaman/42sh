/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbuf_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:28:51 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/03 16:33:24 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		dbuf_remove(t_dbuf *buf, unsigned long pos)
{
	if (!buf || pos > buf->cursor)
		return (LIBFT_ERR);
	if (pos != buf->cursor)
		ft_memmove(buf->buf + pos, buf->buf + pos + 1, buf->cursor - (pos + 1));
	buf->buf[--buf->cursor] = 0;
	return (LIBFT_OK);
}
