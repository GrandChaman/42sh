/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:53:42 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/24 18:20:56 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <unistd.h>
#include "libft.h"
#include <stdlib.h>
#include "ft_printf_format_list.h"

void						handle_padding(t_ptf_buf *buf, t_ptf_param param,
	int len, int att)
{
	if (((att == BEFORE && !param.minus) || (att == AFTER && param.minus))
		&& param.padding > 0 && param.padding > (param.precision - len))
		print_padding(buf, (param.zero ? '0' : ' '), param.padding -
		((param.precision - len <= 0 ? 0 : param.precision - len) + param.neg)
		- len);
}

unsigned long long			absolute_value(long long i)
{
	return ((~0 ^ (unsigned long long)i) + 1);
}

void						ft_putll(t_ptf_buf *buf, unsigned long long n)
{
	char tmp[2];

	tmp[1] = 0;
	if (n > 9)
		ft_putll(buf, n / 10);
	tmp[0] = (n % 10) + '0';
	dbuf_append(&buf->buf, tmp);
}

unsigned long long			extract_nb(t_ptf_param param, va_list ap)
{
	unsigned long long n;

	n = 0;
	if (param.lm == NONE)
		n = (unsigned long long)va_arg(ap, unsigned int);
	else if (param.lm == HH)
		n = (unsigned long long)((unsigned char)va_arg(ap, unsigned int));
	else if (param.lm == H)
		n = (unsigned long long)((unsigned short)va_arg(ap, unsigned int));
	else if (param.lm == L || param.lm == Z || param.lm == J)
		n = (unsigned long long)va_arg(ap, unsigned long);
	else if (param.lm == LL)
		n = (unsigned long long)va_arg(ap, unsigned long long);
	return (n);
}

unsigned long long			extract_nb_signed(t_ptf_param *param, va_list ap)
{
	long long n;

	n = 0;
	if (param->lm == NONE)
		n = (long long)va_arg(ap, int);
	else if (param->lm == HH)
		n = (long long)((char)(va_arg(ap, int)));
	else if (param->lm == H)
		n = (long long)((short)(va_arg(ap, int)));
	else if (param->lm == L || param->lm == Z || param->lm == J)
		n = (long long)va_arg(ap, long);
	else if (param->lm == LL)
		n = (long long)va_arg(ap, long long);
	if (n < 0)
	{
		n = (long long)absolute_value(n);
		param->neg = 1;
	}
	else
		param->neg = 0;
	return ((unsigned long long)n);
}
