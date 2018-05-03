/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 11:08:51 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/07 14:42:48 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_sqrt_top(int nb)
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
			return (m);
		calc = m * m;
	}
	return (m);
}

int				ft_isprime(int nb)
{
	int curr;
	int res;
	int sqrt_nb;

	sqrt_nb = ft_sqrt_top(nb);
	if (nb <= 1)
		return (0);
	curr = 1;
	res = 1;
	while (curr++ < sqrt_nb)
		if (!(nb % curr))
		{
			res = 0;
			break ;
		}
	return (res);
}
