/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 11:33:35 by bluff             #+#    #+#             */
/*   Updated: 2017/12/22 13:11:36 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = 0;
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s2);
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		ft_perror("malloc", "Mallocation failed. Aborting");
	while (s1 && *s1)
		res[i++] = *(s1++);
	while (s2 && *s2)
		res[i++] = *(s2++);
	res[len] = '\0';
	return (res);
}
