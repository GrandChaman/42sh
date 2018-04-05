/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_wstring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:04:53 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/24 18:26:15 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdarg.h>
#include "ft_printf_format_list.h"
#include "libft.h"
#include <wchar.h>
#include <unistd.h>

void	ft_putwchar(t_ptf_buf *buf, unsigned int c)
{
	int				i;
	unsigned char	byte[2];

	byte[0] = c;
	byte[1] = 0;
	if (c <= 127 || MB_CUR_MAX == 1)
		dbuf_append(&buf->buf, (char*)byte);
	else if (c < 2048 || MB_CUR_MAX == 2)
		byte[0] = ((((unsigned int)c >> 6) << 27) >> 27 | WCHAR_1);
	else if ((c > 2047 && c < 65536) || MB_CUR_MAX == 3)
		byte[0] = (((((unsigned int)c >> 12) << 28) >> 28) | WCHAR_2);
	else
		byte[0] = (((((unsigned int)c >> 18) << 29) >> 29) | WCHAR_3);
	if (c <= 127 || MB_CUR_MAX == 1)
		return ;
	dbuf_append(&buf->buf, (char*)byte);
	i = 1 + ((c > 2047 && c < 65536) ? 1 : 0) + (c > 65536 ? 2 : 0);
	i += (i >= MB_CUR_MAX ? (i - MB_CUR_MAX - 1) : 0);
	while (--i >= 0)
	{
		byte[0] = ((((c >> (i * 6)) << 26) >> 26) | WCHAR_GEN);
		dbuf_append(&buf->buf, (char*)byte);
	}
}

void	print_wchar(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param param)
{
	unsigned int		c;

	c = va_arg(buf->ap, unsigned int);
	if (!is_utf8(c))
		return ;
	if (format.len)
		ft_putnstr(buf, format.str, format.len);
	if (c > 255 && c < 2048)
		param.padding -= 1;
	else if ((c > 2047 && c < 65536))
		param.padding -= 2;
	else if (c > 65535 && c < 2097152)
		param.padding -= 3;
	else if (c > 2097151)
		param.padding -= 4;
	handle_padding(buf, param, 1, BEFORE);
	ft_putwchar(buf, c);
	handle_padding(buf, param, 1, AFTER);
}

void	ft_putwstr(t_ptf_buf *buf, wchar_t *c, int len)
{
	int i;
	int o;
	int tmp;

	i = 0;
	o = 0;
	while (c[i] && (o <= len || len < 0))
	{
		tmp = wchar_length((unsigned int)c[i]);
		if ((o + tmp <= len) || (len < 0))
			ft_putwchar(buf, (unsigned int)c[i]);
		o += tmp;
		i++;
	}
}

void	print_wstring(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param p)
{
	wchar_t		*c;
	int			i;
	int			len;

	len = 0;
	i = -1;
	if (format.len)
		ft_putnstr(buf, format.str, format.len);
	if (!(c = va_arg(buf->ap, wchar_t *)))
		c = L"(null)";
	while (c[++i] && (i < p.precision || p.precision < 0))
		if (!is_utf8((unsigned int)c[i]))
			return ;
	len = ft_strwlen(c, p.precision);
	p.padding += (len < p.precision || (len < p.precision && !len)
	? p.precision - len : 0) + (!p.precision ? 1 : 0);
	handle_padding(buf, p, (len = (!len ? 1 : len)), BEFORE);
	if (!len && p.padding > 0)
		print_padding(buf, ' ', 1);
	else
		ft_putwstr(buf, c, p.precision);
	handle_padding(buf, p, len, AFTER);
}
