/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:44:02 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/14 21:23:56 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"

static int	ft_putenv3(const char *str, char ***environ)
{
	char		**ret;
	const int	envlen = arrlen(*environ);
	int			i;
	char		**ep;

	i = 0;
	ep = *environ;
	if (!(ret = (char**)malloc(sizeof(char*) * (envlen + 2))))
		return (ft_error(errno, "malloc"));
	while (ep && *ep)
	{
		ret[i++] = ft_strdup(*ep);
		ep++;
	}
	ret[i++] = (char*)str;
	ret[i] = NULL;
	del_arr(environ);
	*environ = ret;
	return (0);
}

static int	ft_putenv2(const char *str, char ***environ, int matchlen)
{
	char	**ret;
	char	**ep;
	int		i;

	i = 0;
	ep = *environ;
	ret = (char**)malloc(sizeof(char*) * (arrlen(*environ) + 1));
	if (!ret)
		ft_exit(errno, "malloc");
	while (ft_strncmp(str, *ep, matchlen))
	{
		ret[i++] = ft_strdup(*ep);
		ep++;
	}
	ret[i++] = (char*)str;
	++ep;
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

int			ft_putenv(const char *str, char ***environ)
{
	char		**current;
	char		*tmp;
	int			matchlen;

	if (!str)
		return (1);
	if ((tmp = ft_strchr(str, '=')) == NULL || tmp == str)
		matchlen = ft_strlen(str);
	else
		matchlen = (int)(tmp - str);
	++matchlen;
	current = *environ;
	while (current && *current)
	{
		if (ft_strncmp(str, *current, matchlen) == 0)
			return (ft_putenv2(str, environ, matchlen));
		++current;
	}
	return (ft_putenv3(str, environ));
}
