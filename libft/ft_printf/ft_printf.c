/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:38:11 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/20 14:47:52 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_utils.h"
#include "libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int		ft_printf(const char *format, ...)
{
	int			res;
	t_ptf_buf	buf;

	if (!format)
		return (-1);
	va_start(buf.ap, format);
	dbuf_init(&buf.buf);
	res = ft_printf_routine(&buf, format);
	dbuf_print(&buf.buf, STDOUT_FILENO);
	dbuf_destroy(&buf.buf);
	va_end(buf.ap);
	return (res);
}

int		ft_fprintf(int fd, const char *format, ...)
{
	int			res;
	t_ptf_buf	buf;

	if (!format || fd < 0)
		return (-1);
	va_start(buf.ap, format);
	dbuf_init(&buf.buf);
	res = ft_printf_routine(&buf, format);
	dbuf_print(&buf.buf, fd);
	dbuf_destroy(&buf.buf);
	va_end(buf.ap);
	return (res);
}

int		ft_asprintf(char **ret, const char *format, ...)
{
	int			res;
	t_ptf_buf	buf;

	if (!format || !ret)
		return (-1);
	va_start(buf.ap, format);
	dbuf_init(&buf.buf);
	res = ft_printf_routine(&buf, format);
	*ret = buf.buf.buf;
	va_end(buf.ap);
	return (res);
}

int		ft_snprintf(char *ret, size_t size, const char *format, ...)
{
	int			res;
	t_ptf_buf	buf;
	size_t		stop;

	if (!format || !ret)
		return (-1);
	va_start(buf.ap, format);
	dbuf_init(&buf.buf);
	res = ft_printf_routine(&buf, format);
	stop = (size < buf.buf.cursor ? size : buf.buf.cursor);
	ft_memcpy(ret, buf.buf.buf, stop);
	ret[stop] = 0;
	dbuf_destroy(&buf.buf);
	va_end(buf.ap);
	return (res);
}
