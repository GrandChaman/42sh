/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concate_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 22:08:57 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/26 22:08:58 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*concate_array(char **arr)
{
	int		i;
	char	*ret;

	i = 0;
	if (!arr || !*arr)
		return (NULL);
	ret = NULL;
	while (arr[i])
	{
		ret = ft_strfjoin(ret, arr[i++]);
		if (arr[i])
			ret = ft_strfjoin(ret, " ");
	}
	return (ret);
}
