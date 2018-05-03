/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 15:48:30 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 11:56:40 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_pos_in_array(const char c, const char *base)
{
	int i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

static int		ft_atoi_base_routine(const char *nb, const char *base)
{
	int i;
	int nblen;
	int nbbase;
	int res;

	nblen = ft_strlen(nb) - 1;
	nbbase = ft_strlen(base);
	i = -1;
	res = 0;
	while (nb[++i])
		res += ft_pow(nbbase, nblen - i) * get_pos_in_array(nb[i], base);
	return (res);
}

int				ft_atoi_base(const char *nb, const char *base)
{
	int i;
	int res;
	int sign;

	sign = 1;
	i = 0;
	res = 0;
	while (ft_iswhitespace(nb[i]))
		i++;
	if (nb[i] == '-')
		sign = -1;
	if (nb[i] == '-' || nb[i] == '+')
		i++;
	return (sign * ft_atoi_base_routine(nb + i, base));
}
