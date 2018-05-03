/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 13:56:22 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/07 14:37:23 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_next_prime(int nb)
{
	int prime;

	prime = 0;
	while (!prime)
		prime = ft_isprime(nb++);
	return (--nb);
}
