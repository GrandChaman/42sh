/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:44:02 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/19 20:37:22 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"

int		ft_setenv(const char *name, const char *value, int override,
						char ***environ)
{
	char *es;

	if (!name || !name[0] || ft_strchr(name, '='))
		return (ft_error((errno = EINVAL), "setenv"));
	if (ft_getenv(name, environ) != NULL && override == 0)
		return (0);
	es = (char*)malloc(ft_strlen(name) + ft_strlen(value ? value : "") + 2);
	if (es == NULL)
		return (ft_error(errno, "malloc"));
	ft_strcpy(es, name);
	ft_strcat(es, "=");
	value ? ft_strcat(es, value) : (0);
	return (ft_putenv(es, environ));
}
