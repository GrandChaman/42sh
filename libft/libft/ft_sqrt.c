/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 10:39:46 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/06 11:45:28 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nb)
{
	unsigned long start;
	unsigned long end;
	unsigned long m;
	unsigned long n;
	unsigned long calc;

	if (nb < 0)
		return (0);
	n = (unsigned long)nb;
	start = 0;
	end = n / 2;
	m = (end / 2) + 1;
	calc = m * m;
	while (calc != n)
	{
		if (calc > n)
			end = m;
		else
			start = m;
		m += ((calc > n) ? -1 * ((end - start) / 2) : ((end - start) / 2));
		if (m == start || m == end)
			return (0);
		calc = m * m;
	}
	return (m);
}
