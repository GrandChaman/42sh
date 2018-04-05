/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 16:01:53 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 12:03:26 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	void *bckup;

	bckup = dest;
	if (dest <= src)
		while (count--)
			*(unsigned char*)dest++ = *(unsigned char*)src++;
	else
		while (count--)
			*((unsigned char*)dest + count) = *((unsigned char*)src + count);
	return (bckup);
}
