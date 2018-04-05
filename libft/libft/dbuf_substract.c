/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbuf_substract.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:36:42 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/24 16:40:30 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		dbuf_substract(t_dbuf *buf)
{
	if (!buf || buf == 0)
		return (LIBFT_ERR);
	buf->buf[--buf->cursor] = 0;
	return (LIBFT_OK);
}
