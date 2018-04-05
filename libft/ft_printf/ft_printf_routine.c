/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:36:26 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/25 15:39:47 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "libft.h"

void	handle_colors(t_ptf_buf *buf, const char *format, int *li, int *i)
{
	int ii;
	int len;

	ii = -1;
	len = *i + 1;
	while (format[len] && format[len] != '}')
		len++;
	while (g_color_list[++ii].trigger && format[len] == '}')
		if (!ft_strncmp(g_color_list[ii].trigger, format + *i + 1,
			len - *i - 1))
		{
			if ((*i) - *li)
				ft_putnstr(buf, format + *li, (*i) - *li);
			ft_putnstr(buf, g_color_list[ii].code, 0);
			*li = len + 1;
			*i = len;
			break ;
		}
}

int		ft_printf_routine(t_ptf_buf *buf, const char *format)
{
	int			i;
	int			li;

	li = 0;
	i = -1;
	while (format[++i])
		if (format[i] == '%')
		{
			format_handler(buf, get_toprint(format, li, i), &i);
			li = i;
			i--;
		}
		else if (format[i] == '{')
			handle_colors(buf, format, &li, &i);
	dbuf_append(&buf->buf, (char*)format + li);
	return (buf->buf.cursor);
}
