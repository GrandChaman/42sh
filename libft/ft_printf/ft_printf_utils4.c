/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 11:03:16 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/30 13:41:18 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf_utils.h"
#include "ft_printf_format_list.h"
#include "libft.h"
#include <wchar.h>

int									ft_strwlen(wchar_t *str, int max)
{
	int len;
	int i;

	i = -1;
	len = 0;
	if (max >= 0)
	{
		while (str[++i] && max > 0 && len <= max)
			if (len + (wchar_length((unsigned int)str[i])) <= max)
				len += wchar_length((unsigned int)str[i]);
	}
	else
		while (str[++i])
			len += wchar_length((unsigned int)str[i]);
	return (len);
}

unsigned int						wchar_size(unsigned int t)
{
	unsigned int res;

	res = 0;
	while (t)
	{
		res++;
		t >>= 1;
	}
	return (res);
}

int									should_override_zero(char c)
{
	int i;

	i = 0;
	while (DONT_OVERZERO[i])
		if (DONT_OVERZERO[i++] == c)
			return (1);
	return (0);
}

int									is_utf8(unsigned int c)
{
	if ((MB_CUR_MAX == 1 && c > 255) || (MB_CUR_MAX == 2 && c > 2047)
		|| (MB_CUR_MAX == 3 && c > 65535) || (MB_CUR_MAX == 4 && c > 2097151) ||
		c > 0x10ffff || (c > 0xD7ff && c < 0xe000))
		return (0);
	return (1);
}

int									wchar_length(unsigned int c)
{
	if (c <= 127 || MB_CUR_MAX == 1)
		return (1);
	else if ((c > 127 && c < 2048) || MB_CUR_MAX == 2)
		return (2);
	else if ((c > 2047 && c < 65536) || MB_CUR_MAX == 3)
		return (3);
	else
		return (4);
}
