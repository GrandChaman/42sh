/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbuf_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:02:25 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/24 11:44:00 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		dbuf_init(t_dbuf *buf)
{
	if (!buf)
		return (LIBFT_ERR);
	buf->buf = ft_strnew(BUFF_SIZE);
	buf->len = BUFF_SIZE;
	buf->cursor = 0;
	return (LIBFT_OK);
}
