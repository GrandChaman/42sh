/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:18:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/24 22:09:24 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdarg.h>
#include "ft_printf_format_list.h"
#include "libft.h"

void	print_signed(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param p)
{
	unsigned long long	n;
	int					len;

	if (format.len)
		ft_putnstr(buf, format.str, format.len);
	n = extract_nb_signed(&p, buf->ap);
	len = ft_nblen(n) + (!n ? 1 : 0);
	p.padding += (!p.precision && !n ? 1 : 0);
	p.padding -= (((p.plus || (p.space && (len < p.padding
					|| p.padding <= 0))) && !p.neg) ? 1 : 0);
	if (p.space)
		print_padding(buf, (p.neg ? '-' : ' '), 1);
	if ((p.plus || p.neg) && p.zero && !p.space)
		print_padding(buf, (p.neg ? '-' : '+'), 1);
	handle_padding(buf, p, len, BEFORE);
	if ((p.plus || p.neg) && !p.zero && !p.space)
		print_padding(buf, (p.neg ? '-' : '+'), 1);
	if (p.precision > 0)
		print_padding(buf, '0', p.precision - len);
	if (!(!p.precision && !n))
		ft_putll(buf, n);
	handle_padding(buf, p, len, AFTER);
}

void	print_unsigned(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param param)
{
	unsigned long long	n;
	int					len;

	if (format.len)
		ft_putnstr(buf, format.str, format.len);
	n = extract_nb(param, buf->ap);
	len = ft_nblen(n);
	len = (n ? len : 1);
	handle_padding(buf, param, len, BEFORE);
	if (param.hashtag)
		print_padding(buf, '0', 1);
	if (param.precision > 0)
		print_padding(buf, '0', param.precision - len);
	if (param.precision || n)
		ft_putll(buf, n);
	handle_padding(buf, param, len, AFTER);
}

void	print_octal(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param param)
{
	unsigned long long	n;
	int					len;
	char				*istr;

	if (format.len)
		ft_putnstr(buf, format.str, format.len);
	n = extract_nb(param, buf->ap);
	istr = ft_itoa_base(n, 8);
	len = ft_strlen(istr);
	param.padding += (!param.precision && !n ? 1 : 0);
	param.padding -= (param.hashtag && n ? 1 : 0);
	handle_padding(buf, param, len, BEFORE);
	if (param.hashtag && ((n && param.precision <= len) || !param.precision))
		print_padding(buf, '0', 1);
	if (param.precision > 0)
		print_padding(buf, '0', param.precision - len);
	if (n || param.precision)
		ft_putnstr(buf, istr, len);
	handle_padding(buf, param, len, AFTER);
	free(istr);
}

void	print_hex(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param param)
{
	hex_handler(LR, buf, format, param);
}

void	print_pointer(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param param)
{
	param.hashtag = 1;
	param.lm = L;
	hex_handler(PTR, buf, format, param);
}
