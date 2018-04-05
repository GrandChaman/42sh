/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 01:11:03 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 11:45:30 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *lhs, const char *rhs)
{
	while (*lhs == *rhs && *lhs && *rhs)
	{
		lhs++;
		rhs++;
	}
	return ((unsigned char)*lhs - (unsigned char)*rhs);
}
