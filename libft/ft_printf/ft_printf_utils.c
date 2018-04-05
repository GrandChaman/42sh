/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:53:42 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/24 22:45:04 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <unistd.h>
#include "libft.h"
#include <stdlib.h>

int					ft_nblen(unsigned long long nb)
{
	if (!nb)
		return (0);
	return (ft_nblen(nb / 10) + 1);
}

void				print_padding(t_ptf_buf *buf, char c, int len)
{
	char tmp[2];

	if (len <= 0)
		return ;
	tmp[0] = c;
	tmp[1] = 0;
	while (len--)
		dbuf_append(&buf->buf, tmp);
}

int					ft_strccmp(const char *lhs, const char *rhs)
{
	int i;

	i = 0;
	while (lhs[i] == rhs[i] && lhs[i] && rhs[i])
		i++;
	return (i);
}

int					ft_strnccmp(const char *lhs, const char *rhs, int max)
{
	int i;

	i = 0;
	while (lhs[i] == rhs[i] && lhs[i] && rhs[i] && i < max)
		i++;
	return (i);
}

void				ft_putnstr(t_ptf_buf *buf, const char *str, int stop)
{
	char	tmp[2];
	int		i;

	i = -1;
	tmp[1] = 0;
	if (!stop)
		stop = ft_strlen(str);
	while (++i < stop)
	{
		tmp[0] = str[i];
		dbuf_append(&buf->buf, tmp);
	}
}
