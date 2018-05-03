/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 15:39:09 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 11:45:52 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t count)
{
	unsigned int i;
	unsigned int ii;

	i = ft_strlen(dest);
	ii = 0;
	while (src[ii] && ii < count)
	{
		dest[i + ii] = src[ii];
		ii++;
	}
	dest[i + ii] = '\0';
	return (dest);
}
