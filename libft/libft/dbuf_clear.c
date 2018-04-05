/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbuf_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:07:01 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/24 11:44:16 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		dbuf_clear(t_dbuf *buf)
{
	if (!buf || !buf->buf)
		return (LIBFT_ERR);
	ft_bzero(buf->buf, buf->len);
	buf->cursor = 0;
	return (LIBFT_OK);
}
