/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 12:56:06 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 11:45:47 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int i;
	unsigned int ii;
	unsigned int res;

	i = ft_strlen(dst);
	res = i;
	if (i > size)
	{
		res = size;
		size = i;
	}
	ii = 0;
	if (size <= 0)
		return (res + ft_strlen(src));
	while (src[ii] && i + ii < size - 1)
	{
		dst[i + ii] = src[ii];
		ii++;
	}
	dst[i + ii] = '\0';
	return (res + ft_strlen(src));
}
