/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 00:12:49 by bluff             #+#    #+#             */
/*   Updated: 2018/04/16 18:34:29 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	char *nstr;

	if (!str)
		return (NULL);
	if (!(nstr = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		ft_perror("malloc", "Mallocation failed. Aborting");
	ft_strcpy(nstr, str);
	return (nstr);
}
