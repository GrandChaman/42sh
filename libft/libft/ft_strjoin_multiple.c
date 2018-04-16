/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_multiple.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:12:05 by fbertoia          #+#    #+#             */
/*   Updated: 2018/01/31 18:12:06 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

char	*ft_strjoin_multiple(int nb_args, ...)
{
	va_list	ap;
	int		i;
	char	*tmp;
	char	*ret;

	i = 1;
	tmp = NULL;
	va_start(ap, nb_args);
	if (nb_args <= 0)
		return (NULL);
	ret = ft_strdup(va_arg(ap, char *));
	while (i < nb_args)
	{
		tmp = ret;
		if ((ret = ft_strjoin(tmp, va_arg(ap, char *))) == NULL)
			return (NULL);
		ft_memdel((void**)&tmp);
		i++;
	}
	va_end(ap);
	return (ret);
}
