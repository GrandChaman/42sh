/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 11:16:47 by bluff             #+#    #+#             */
/*   Updated: 2017/12/22 13:11:45 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*res;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		ft_perror("malloc", "Mallocation failed. Aborting");
	res[len] = '\0';
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	return (res);
}
