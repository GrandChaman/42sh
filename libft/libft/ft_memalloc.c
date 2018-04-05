/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 20:09:11 by bluff             #+#    #+#             */
/*   Updated: 2017/12/22 13:11:20 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void *res;

	if (!(res = malloc(size)))
		ft_perror("malloc", "Mallocation failed. Aborting");
	ft_memset(res, 0, size);
	return (res);
}
