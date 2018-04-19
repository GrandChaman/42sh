/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 17:04:12 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/18 18:47:44 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int				ft_error(int err, const char *s)
{
	if (err >= 0)
		ft_fprintf(2, "42sh: %s: %s\n", s, g_errno_message[err]);
	else
	{
		err = -err;
		ft_fprintf(2, "42sh: %s: %s\n", s, g_own_message[err]);
	}
	return (err);
}

static char		*random_str2(int *fd, char **ret, size_t len)
{
	*fd = open("/dev/urandom", O_RDONLY);
	if (*fd < 0)
	{
		ft_error(errno, "/dev/urandom");
		return (NULL);
	}
	if (!(*ret = ft_strnew(len)))
	{
		ft_error(errno, "malloc");
		return (NULL);
	}
	return (*ret);
}

static const char g_base[] = "0123456789abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char			*random_str(size_t len)
{
	int				fd;
	char			*ret;
	unsigned char	tmp;

	if ((ret = random_str2(&fd, &ret, len)) == NULL)
		return (NULL);
	ret[len--] = 0;
	while (len--)
	{
		if (read(fd, &tmp, 1) < 0)
		{
			ft_error(errno, "read /dev/urandom");
			return (NULL);
		}
		ret[len] = g_base[tmp % 62];
	}
	close(fd);
	return (ret);
}
