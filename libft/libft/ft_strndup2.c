/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 12:41:49 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/17 13:19:02 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup2(char *str, size_t n)
{
	char	*nstr;
	size_t	len;

	if (!str || !n)
		return (NULL);
	len = ft_strlen(str);
	len = (len > n ? n : len);
	nstr = ft_strnew(n);
	ft_strncpy(nstr, str, n);
	return (nstr);
}
