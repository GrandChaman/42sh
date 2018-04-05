/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_alnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 01:49:02 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/03 01:49:04 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		str_isprint(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		str_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}
