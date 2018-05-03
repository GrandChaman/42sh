/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:53:42 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/25 15:17:58 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "ft_printf_format_list.h"
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>

const char		*parse_param(t_ptf_param *res, const char *format,
	int *i, va_list ap)
{
	int tmp;
	int offset;

	init_param(res);
	tmp = 0;
	offset = 0;
	while (format + offset)
	{
		tmp = *i;
		if (*(format + offset) >= ' ' && *(format + offset) <= 'z' &&
		g_param_list[*(format + offset) - ' '])
			g_param_list[*(format + offset) - ' '](format + offset, res, i, ap);
		else
			break ;
		if (!(tmp = *i - tmp))
			break ;
		offset += tmp;
	}
	return (format + offset);
}

t_ptf_toprint	get_toprint(const char *format, int start, int stop)
{
	t_ptf_toprint res;

	res.format = format + stop + 1;
	res.str = format + start;
	res.start = start;
	res.len = stop - start;
	return (res);
}

void			format_handler(t_ptf_buf *buf, t_ptf_toprint format, int *i)
{
	int				ii;
	t_ptf_format	fmt;
	int				l;
	int				tmp;
	t_ptf_param		param;

	ii = -1;
	(*i)++;
	format.format = parse_param(&param, format.format, i, buf->ap);
	l = 0;
	while (g_format_list[++ii].f)
	{
		tmp = ft_strccmp(g_format_list[ii].trigger, format.format);
		if (tmp > l)
		{
			l = tmp;
			fmt = g_format_list[ii];
		}
	}
	if (l == 0 || !fmt.f)
		return ;
	*i += l;
	fmt.f(buf, format, param);
}
