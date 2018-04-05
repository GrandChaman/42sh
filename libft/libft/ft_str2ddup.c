/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2ddup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:09:20 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/14 11:25:49 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_str2ddup(char **arr)
{
	char	**res;
	int		i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr && arr[i])
		i++;
	res = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	res[i] = NULL;
	i = -1;
	while (arr && arr[++i])
		*(res + i) = ft_strdup(*(arr + i));
	return (res);
}
