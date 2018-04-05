/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allauren <allauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 03:21:03 by allauren          #+#    #+#             */
/*   Updated: 2017/12/05 14:26:50 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf_utils.h"
#include "ft_printf_format_list.h"
#include "libft.h"

int								is_format_identifier(const char *str)
{
	int i;

	i = -1;
	while (g_format_list[++i].trigger)
		if (ft_strccmp(g_format_list[i].trigger, str))
			return (1);
	return (0);
}

int								is_arguments(const char *str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (FLAG_LIST[i])
		if (ft_strccmp(&FLAG_LIST[i++], str))
			res = 1;
	return (res);
}

void							ft_strtolower(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
}
