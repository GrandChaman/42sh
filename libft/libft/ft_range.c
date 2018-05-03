/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:26:25 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/22 13:11:28 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	*ft_range(int min, int max)
{
	unsigned int	r;
	unsigned int	i;
	int				*res;

	i = 0;
	if (max <= min)
		return (0);
	r = (unsigned int)(max - min);
	if (!(res = (int*)malloc(sizeof(int) * r)))
		ft_perror("malloc", "Mallocation failed. Aborting");
	while (i < r)
	{
		res[i] = min++;
		i++;
	}
	return (res);
}
