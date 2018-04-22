/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 20:49:07 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/22 16:17:38 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft.h"

char	**cpy_arr(char **arr)
{
	char	**ret;
	int		i;

	i = 0;
	if (!arr || !*arr)
		return (NULL);
	while (arr[i])
		i++;
	ret = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	if (!ret)
		return (NULL);
	ret[i] = NULL;
	while (--i >= 0)
		ret[i] = ft_strdup(arr[i]);
	return (ret);
}
