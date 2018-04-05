/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 13:08:56 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/13 13:10:11 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

const char	*ft_getenv(char *search, const char **env)
{
	int					i;
	unsigned long long	pos;

	i = 0;
	while (env + i && *(env + i))
	{
		pos = (unsigned long long)(ft_strchr(*(env + i), '='));
		if (pos)
			pos -= (unsigned long long)*(env + i);
		if (pos && !ft_strncmp(search, *(env + i), pos))
			return (*(env + i) + pos + 1);
		i++;
	}
	return (NULL);
}
