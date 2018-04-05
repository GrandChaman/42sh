/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stralike.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:36:02 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/21 16:36:08 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stralike(char *str1, char *str2, size_t len)
{
	unsigned int i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < len)
		i++;
	if (str1[i] == str2[i] && str1[i] == 0)
		return (-1);
	return (len - i);
}
