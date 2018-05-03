/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 00:12:49 by bluff             #+#    #+#             */
/*   Updated: 2018/04/22 16:18:14 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <errno.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (!src)
		return (i);
	while (src[i] != 0 && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < size)
	{
		dst[i] = 0;
		i++;
	}
	return (i);
}

char	*ft_strndup(char *str, size_t size)
{
	char *tmp;

	if (!str || size <= 0)
		return (NULL);
	tmp = (char *)ft_memalloc(sizeof(char) * size);
	if (tmp == NULL)
		exit(0);
	ft_strlcpy(tmp, str, size);
	return (tmp);
}
