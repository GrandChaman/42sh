/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbuf_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:41:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/24 16:43:10 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		dbuf_print(t_dbuf *buf, unsigned char fd)
{
	if (!buf)
		return (LIBFT_ERR);
	write(fd, buf->buf, buf->cursor);
	return (LIBFT_OK);
}
