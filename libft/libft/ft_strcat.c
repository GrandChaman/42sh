/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 15:39:09 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 11:45:28 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int i;
	int ii;

	i = ft_strlen(dest);
	ii = -1;
	while (src[++ii])
		dest[i + ii] = src[ii];
	dest[i + ii] = '\0';
	return (dest);
}
