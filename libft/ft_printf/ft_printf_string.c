/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:04:53 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/24 22:27:36 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdarg.h>
#include "ft_printf_format_list.h"
#include "libft.h"

char	*get_null_str(int empty)
{
	if (empty)
		return ("");
	return ("(null)");
}

void	print_string(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param p)
{
	char	*str;
	int		len;

	if (p.lm == L)
		return (print_wstring(buf, format, p));
	if (format.len)
		ft_putnstr(buf, format.str, format.len);
	if (!(str = va_arg(buf->ap, char *)))
		str = get_null_str(!p.precision);
	len = ft_strlen(str);
	p.padding += (!p.precision && len ? len : 0);
	p.precision = (p.precision > len ? len : p.precision);
	if (!p.minus && p.padding > 0)
		print_padding(buf, (p.zero ? '0' : ' '), p.padding
		- (p.precision <= 0 ? len : p.precision));
	if (p.precision && len)
		ft_putnstr(buf, str, p.precision < 0 ? 0 : p.precision);
	else if (!p.precision && !ft_strcmp(str, "(null)") && !p.zero)
		ft_putnstr(buf, " ", 0);
	if (p.minus && p.padding > 0)
		print_padding(buf, (p.zero ? '0' : ' '), p.padding -
		(p.precision <= 0 ? len : p.precision));
}

void	print_char(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param param)
{
	char	c;

	if (param.lm == L)
		return (print_wchar(buf, format, param));
	if (format.len)
		ft_putnstr(buf, format.str, format.len);
	c = (char)va_arg(buf->ap, int);
	if (!param.minus && param.padding > 0)
		print_padding(buf, (param.zero ? '0' : ' '), param.padding - 1);
	if (c)
		ft_putnstr(buf, &c, 1);
	else
		dbuf_insert(&buf->buf, buf->buf.cursor, '\0');
	if (param.minus && param.padding > 0)
		print_padding(buf, (param.zero ? '0' : ' '), param.padding -
		(param.precision > 0 ? param.precision : 1));
}

void	print_pourcent(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param param)
{
	if (format.len)
		ft_putnstr(buf, format.str, format.len);
	if (!param.minus && param.padding > 0)
		print_padding(buf, (param.zero ? '0' : ' '), param.padding - 1);
	ft_putnstr(buf, "%", 0);
	if (param.minus && param.padding > 0)
		print_padding(buf, ' ', param.padding - 1);
}
