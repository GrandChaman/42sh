/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 18:43:07 by hfontain          #+#    #+#             */
/*   Updated: 2018/02/19 17:33:40 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpop(char *str, size_t idx)
{
	size_t	ln;

	if (!str)
		return (NULL);
	ln = ft_strlen(str);
	if (idx >= ln)
		return (str);
	if (ln < 1)
		return (str);
	ft_memmove(str + idx, str + idx + 1, ln - idx);
	return (str);
}

char	*ft_strpopm(char *str, size_t idx)
{
	char	*new;
	size_t	ln;

	if (!str)
		return (NULL);
	ln = ft_strlen(str);
	if (idx >= ln)
		return (ft_strdup(str));
	if (ln < 1)
	{
		new = ft_strdup("");
		return (new);
	}
	new = ft_strnew(ln - 1);
	ft_strncpy(new, str, idx);
	ft_strcat(new, str + idx + 1);
	ft_strdel(&str);
	return (new);
}
