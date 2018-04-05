/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 00:55:16 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 12:27:11 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strstr(const char *str, const char *substr)
{
	int i;
	int ii;

	i = 0;
	if (!substr[0])
		return ((char*)str);
	while (str[i])
	{
		ii = 0;
		while (substr[ii] == str[i + ii] && substr[ii] && str[i + ii])
			ii++;
		if (!substr[ii])
			return ((char*)str + i);
		i++;
	}
	return (NULL);
}
