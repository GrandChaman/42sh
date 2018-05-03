/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 20:31:51 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 12:23:57 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int res;

	if (s1 == NULL || s2 == NULL)
		return (0);
	res = ft_strncmp(s1, s2, n);
	return (!res ? 1 : 0);
}
