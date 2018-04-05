/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str3join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 15:21:05 by vbaudot           #+#    #+#             */
/*   Updated: 2018/02/28 15:53:14 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str3join(char const *s1, char const *s2, char const *s3)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (s1 && s2 && s3)
	{
		ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
		if (ret)
		{
			ret = ft_strcpy(ret, s1);
			ret = ft_strcat(ret, s2);
			ret = ft_strcat(ret, s3);
		}
	}
	return (ret);
}
