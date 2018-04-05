/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers_upper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:18:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/25 15:07:13 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdarg.h>
#include "ft_printf_format_list.h"
#include "libft.h"

void	print_octal_upper(t_ptf_buf *buf, t_ptf_toprint format,
	t_ptf_param param)
{
	param.lm = L;
	print_octal(buf, format, param);
}

void	print_unsigned_upper(t_ptf_buf *buf, t_ptf_toprint format,
	t_ptf_param param)
{
	param.lm = L;
	print_unsigned(buf, format, param);
}

void	print_signed_upper(t_ptf_buf *buf, t_ptf_toprint format,
	t_ptf_param param)
{
	param.lm = L;
	print_signed(buf, format, param);
}

void	hex_handler(int mode, t_ptf_buf *buf, t_ptf_toprint format,
	t_ptf_param p)
{
	unsigned long long	n;
	int					len;
	char				*istr;

	if (format.len)
		ft_putnstr(buf, format.str, format.len);
	n = extract_nb(p, buf->ap);
	istr = ft_itoa_base(n, 16);
	if (mode == LR || mode == PTR)
		ft_strtolower(istr);
	len = ft_strlen(istr);
	p.padding -= (mode == PTR || (p.hashtag && (n || mode == PTR)) ? 2 : 0);
	if ((mode == PTR || (p.hashtag && n)) && p.zero)
		ft_putnstr(buf, (mode == LR || mode == PTR ? "0x" : "0X"), 2);
	handle_padding(buf, p, (n || p.precision ? len : -1), BEFORE);
	if ((mode == PTR || (p.hashtag && n)) && !p.zero)
		ft_putnstr(buf, (mode == LR || mode == PTR ? "0x" : "0X"), 2);
	(p.precision > 0 ? print_padding(buf, '0', p.precision - len) : 0);
	if (n || p.precision)
		ft_putnstr(buf, istr, len);
	handle_padding(buf, p, (n || p.precision ? len : -1), AFTER);
	free(istr);
}

void	print_hex_upper(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param param)
{
	hex_handler(UP, buf, format, param);
}
