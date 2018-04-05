/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:45:16 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/05 14:01:07 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"

int			change_oldpwd_pwd(char ***environ, const char* path)
{
	char	buf[PATH_MAX];

	ft_setenv("OLDPWD", ft_getenv("PWD", environ), 1, environ);
	if (path)
		ft_setenv("PWD", path, 1, environ);
	else
		ft_setenv("PWD", getcwd(buf, PATH_MAX - 1), 1, environ);
	return (0);
}

int			bi_cd(int argc, char **argv, char ***environ)
{
	const char		*home = ft_getenv("HOME", environ);
	const char		*oldpwd = ft_getenv("OLDPWD", environ);
	int				p;
	int				idx;

	p = 0;
	idx = 1;
	if (argc < 2)
	{
		if (!chdir(home))
			return (change_oldpwd_pwd(environ, NULL));
		return (ft_error(-3, "cd"));
	}
	if (argv[1][0] == '-' && (argv[1][1] == 'P' || argv[1][1] == 'L'))
	{
		++idx;
		p = (argv[1][1] == 'P');
	}
	if (ft_strequ(argv[idx], "-"))
	{
		if (!oldpwd)
			return (ft_error(-7, "cd"));
		if (!chdir(oldpwd))
			return (change_oldpwd_pwd(environ, NULL));
		return (ft_error(-4, "cd"));
	}
	if (chdir(argv[idx]) == 0)
		return (change_oldpwd_pwd(environ, p ? NULL : argv[idx]));
	else
		return (ft_error(errno, "cd"));
}
