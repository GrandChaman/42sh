/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 20:26:15 by bluff             #+#    #+#             */
/*   Updated: 2018/04/16 15:15:03 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int		i;
	char	c;

	c = ch;
	i = ft_strlen(str);
	while (i >= 0)
		if (str[i] == ch)
			return ((char*)str + i);
		else
			i--;
	return (NULL);
}

char	*ft_strrchr_2(const char *s, int c)
{
	char	*ret;
	int		i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	ret = (char *)s;
	if (!c)
		return (ret + i);
	i--;
	while (i > 0 && ret[i] != c)
		i--;
	if (ret[i] == c)
		return (ret + i);
	else
		return (NULL);
}
