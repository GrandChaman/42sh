/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:42:16 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/15 15:58:29 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"
#include "env.h"

char	*ft_getenv(const char *name, char ***environ)
{
	int				i;
	const size_t	len = ft_strlen(name);

	i = 0;
	if (!name || !name[0] || ft_strchr(name, '=') || !environ || !*environ)
		return (NULL);
	while ((*environ)[i])
	{
		if (ft_strncmp(name, (*environ)[i], len) == 0
			&& (*environ)[i][len] == '=')
			return (ft_strchr((*environ)[i], '=') + 1);
		i++;
	}
	return (NULL);
}
