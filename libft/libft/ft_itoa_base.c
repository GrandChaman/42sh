/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:17:18 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/05 14:17:27 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void						ft_recursive(char *str, unsigned long long nb,
			unsigned long long base, unsigned long long i)
{
	if (i >= base)
	{
		if ((nb / i) < 10)
			*str = nb / i + '0';
		else
			*str = nb / i - 10 + 'A';
		ft_recursive((str + 1), (nb % i), base, (i / base));
		return ;
	}
	if (nb / i < 10)
		*str = nb / i + '0';
	else
		*str = nb / i - 10 + 'A';
}

char							*ft_itoa_base(unsigned long long nb, int base)
{
	unsigned long long	i;
	unsigned long long	t;
	char				*str;
	unsigned long long	count;
	unsigned long long	j;

	i = 1;
	count = 0;
	t = nb;
	j = 0;
	while ((t /= base))
		count++;
	count++;
	while (j++ < (count - 1))
		i = i * base;
	if (base < 2 || !(str = ft_strnew(count)))
		return (NULL);
	str[count] = '\0';
	if (nb == 0)
		str[0] = '0';
	else
		ft_recursive(str, nb, base, i);
	return (str);
}
