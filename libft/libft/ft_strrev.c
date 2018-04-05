/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 12:23:57 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/22 13:11:52 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strrev(char *str)
{
	int		i;
	int		s;
	char	*tmp;

	s = ft_strlen(str);
	if (!(tmp = (char*)malloc(sizeof(char) * (s + 1))))
		ft_perror("malloc", "Mallocation failed. Aborting");
	i = -1;
	while (++i < s)
		tmp[(s - 1) - i] = str[i];
	ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}
