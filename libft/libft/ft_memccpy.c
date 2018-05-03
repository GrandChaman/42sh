/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 15:13:15 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 11:45:15 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char lc;

	lc = c;
	while (n--)
	{
		*(unsigned char*)dest++ = *(unsigned char*)src;
		if (*(unsigned char*)src++ == lc)
			return (dest);
	}
	return (NULL);
}
