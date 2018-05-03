/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <fbertoia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:39:19 by fbertoia          #+#    #+#             */
/*   Updated: 2018/05/03 00:42:56 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpushback(char *str, char c, size_t *buff_sz)
{
	if (!str)
		str = ft_strnew(*buff_sz);
	return (ft_strpush(str, ft_strlen(str), c, buff_sz));
}

char	*ft_strpush(char *str, size_t idx, char c, size_t *buff_sz)
{
	size_t	ln;
	char	*new;

	*buff_sz += *buff_sz ? 0 : 2;
	ln = ft_strlen(str);
	if (idx > ln)
		return (str);
	if (!str || ln == 0)
	{
		new = ft_strnew(*buff_sz > 1 ? *buff_sz : 2);
		new[0] = c;
		ft_strdel(&str);
		return (new);
	}
	new = str;
	if (*buff_sz - 1 <= ln)
	{
		new = ft_strndup(str, *buff_sz * 2);
		*buff_sz *= 2;
		ft_strdel(&str);
	}
	ft_memmove(new + idx + 1, new + idx, ln - idx);
	new[idx] = c;
	return (new);
}

char	*ft_strpushm(char *str, size_t idx, char c)
{
	char	*new;
	size_t	ln;

	if (!str)
	{
		new = ft_strnew(1);
		new[0] = c;
		return (new);
	}
	ln = ft_strlen(str);
	if (ln == 0)
	{
		new = ft_strnew(1);
		new[0] = c;
		ft_strdel(&str);
		return (new);
	}
	if (idx > ln)
		return (str);
	new = ft_strnew(ln + 1);
	ft_strncpy(new, str, idx);
	ft_strncat(new, &c, 1);
	ft_strcat(new, str + idx);
	ft_strdel(&str);
	return (new);
}
