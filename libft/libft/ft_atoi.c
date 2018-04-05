/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 17:47:51 by bluff             #+#    #+#             */
/*   Updated: 2017/11/09 11:48:15 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_issign(char c, int *i, int *sign)
{
	if (c == '-')
		*sign = -1;
	if (c == '+' || c == '-')
		(*i)++;
}

static int	check_for_longlong(const char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (i > 19)
		return (1);
	else if (i < 19)
		return (0);
	else if (ft_strcmp("9223372036854775807", str) <= 0)
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int i;
	int ii;
	int sign;
	int res;

	res = 0;
	sign = 1;
	i = 0;
	ii = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	ft_issign(str[i], &i, &sign);
	while (str[i] == '0')
		i++;
	if (check_for_longlong(str + i))
		return (sign == 1 ? -1 : 0);
	while (ft_isdigit(str[i + ii]))
	{
		res *= 10;
		res += str[i + ii] - '0';
		ii++;
	}
	return (sign * res);
}
