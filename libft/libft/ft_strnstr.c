/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 17:34:24 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 12:24:33 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *str, const char *substr, size_t count)
{
	unsigned int i;
	unsigned int ii;

	i = 0;
	if (!substr[0])
		return ((char*)str);
	while (str[i] && i < count)
	{
		ii = 0;
		while (substr[ii] == str[i + ii] && substr[ii] &&
			str[i + ii] && i + ii < count)
			ii++;
		if (!substr[ii])
			return ((char*)str + i);
		i++;
	}
	return (NULL);
}
