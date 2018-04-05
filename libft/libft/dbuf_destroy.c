/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbuf_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:03:15 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/24 11:44:20 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		dbuf_destroy(t_dbuf *buf)
{
	if (!buf)
		return (LIBFT_ERR);
	free(buf->buf);
	buf->buf = NULL;
	buf->len = 0;
	buf->cursor = 0;
	return (LIBFT_OK);
}
