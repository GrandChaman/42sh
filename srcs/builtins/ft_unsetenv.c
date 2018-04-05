/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:43:37 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/19 20:37:26 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"

static int	ft_unsetenv2(const char *name, char ***environ)
{
	char			**ep;
	char			**ret;
	const size_t	len = ft_strlen(name);
	int				i;

	i = 0;
	ep = *environ;
	ret = (char **)malloc(sizeof(char*) * arrlen(*environ));
	if (!ret)
		ft_exit(errno, "malloc");
	while (ft_strncmp(*ep, name, len) || (*ep)[len] != '=')
	{
		ret[i++] = ft_strdup(*ep);
		ep++;
	}
	ep++;
	while (*ep)
	{
		ret[i++] = ft_strdup(*ep);
		ep++;
	}
	ret[i] = NULL;
	del_arr(environ);
	*environ = ret;
	return (0);
}

int			ft_unsetenv(const char *name, char ***environ)
{
	char			**ep;
	const size_t	len = ft_strlen(name);

	if (!environ || !*environ)
		return (0);
	if (!name || !name[0] || ft_strchr(name, '='))
	{
		errno = EINVAL;
		return (ft_error(errno, "unsetenv"));
	}
	ep = *environ;
	while (*ep)
	{
		if (ft_strncmp(*ep, name, len) == 0 && (*ep)[len] == '=')
			return (ft_unsetenv2(name, environ));
		else
			++ep;
	}
	return (0);
}
