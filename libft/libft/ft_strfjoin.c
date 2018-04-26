/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:44:53 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/16 15:12:41 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		*null_case(char const *s1, char const *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	else
		return (ft_strdup(s1));
}

char			*ft_strfjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	char	*p;

	i = 0;
	if (!s1 || !s2)
	{
		ret = null_case(s1, s2);
		ft_strdel(&s1);
		return (ret);
	}
	if ((ret = (char *)malloc(sizeof(char) * (ft_strlen(s1)
		+ ft_strlen(s2) + 1))) == NULL)
		return (NULL);
	p = s1;
	while (*s1)
		ret[i++] = *(s1++);
	ft_strdel(&p);
	while (*s2)
		ret[i++] = *(s2++);
	ret[i] = 0;
	return (ret);
}

char			*ft_strffjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	char	*p;

	i = 0;
	if (!s1 || !s2)
	{
		ret = null_case(s1, s2);
		ft_strdel(&s1);
		ft_strdel(&s2);
		return (ret);
	}
	if ((ret = (char *)malloc(sizeof(char) * (ft_strlen(s1)
		+ ft_strlen(s2) + 1))) == NULL)
		return (NULL);
	p = s1;
	while (*s1)
		ret[i++] = *(s1++);
	ft_strdel(&p);
	p = s2;
	while (*s2)
		ret[i++] = *(s2++);
	ft_strdel(&p);
	ret[i] = 0;
	return (ret);
}
