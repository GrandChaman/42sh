/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 12:41:49 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/16 15:14:37 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup2(char *str, size_t size)
{
	char *tmp;

	if (!str || size <= 0)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * size);
	if (tmp == NULL)
		exit(0);
	ft_strlcpy(tmp, str, size);
	return (tmp);
}
