/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbuf_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:42:04 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/03 17:02:01 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		dbuf_insert(t_dbuf *buf, unsigned long pos, char to_insert)
{
	char *tmp;

	if (!buf || pos > buf->cursor)
		return (LIBFT_ERR);
	if (buf->cursor + 1 > buf->len)
	{
		tmp = ft_strnew(buf->len + BUFF_SIZE);
		ft_memcpy(tmp, buf->buf, pos + 1);
		tmp[pos] = to_insert;
		ft_memcpy(tmp + pos + 1, buf->buf + pos, buf->cursor - pos);
		free(buf->buf);
		buf->len += BUFF_SIZE;
		buf->buf = tmp;
	}
	else
	{
		ft_memmove(buf->buf + pos + 1, buf->buf + pos, buf->cursor - pos);
		buf->buf[pos] = to_insert;
	}
	buf->cursor++;
	return (LIBFT_OK);
}
