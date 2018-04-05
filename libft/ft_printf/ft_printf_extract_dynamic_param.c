/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_extract_dynamic_param.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:35:44 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/30 14:41:37 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "libft.h"
#include <stdarg.h>

int		extract_dyn_param(int *minus, va_list ap)
{
	int res;

	res = va_arg(ap, long);
	if (res < 0)
	{
		res *= -1;
		if (minus)
			*minus = 1;
		else
			return (-1);
	}
	return ((int)res);
}
