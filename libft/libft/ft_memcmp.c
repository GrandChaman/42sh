/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 19:05:06 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 12:02:57 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *lhs, const void *rhs, size_t count)
{
	unsigned int		i;
	const unsigned char	*fbuf;
	const unsigned char	*sbuf;

	i = 0;
	fbuf = lhs;
	sbuf = rhs;
	if (!count)
		return (0);
	while (*(fbuf + i) == *(sbuf + i) && i < count - 1)
		i++;
	return ((i == count) ? 0 : *(fbuf + i) - *(sbuf + i));
}
