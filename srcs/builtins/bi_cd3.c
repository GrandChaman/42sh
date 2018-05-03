/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 23:56:42 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/16 23:56:45 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*cd_rules5_2(char *curpath)
{
	curpath = ft_strjoin("./", curpath);
	if (!ft_is_dir(curpath, 1))
	{
		ft_strdel(&curpath);
		return (NULL);
	}
	return (curpath);
}

int		change_oldpwd_pwd(char ***environ, const char *path)
{
	char	buf[PATH_MAX];

	ft_setenv("OLDPWD", ft_getenv("PWD", environ), 1, environ);
	if (path)
		ft_setenv("PWD", path, 1, environ);
	else
		ft_setenv("PWD", getcwd(buf, PATH_MAX - 1), 1, environ);
	return (0);
}

int		go_home(char ***environ)
{
	const char		*home = ft_getenv("HOME", environ);

	if (!chdir(home))
		return (change_oldpwd_pwd(environ, NULL));
	return (ft_error(-3, "cd"));
}

int		ft_is_dir(char *buf, int print)
{
	struct stat file_stat;

	if (lstat(buf, &file_stat) < 0)
	{
		if (print)
			ft_error(errno, "cd");
		return (0);
	}
	if (!(S_ISDIR(file_stat.st_mode)) && !(S_ISLNK(file_stat.st_mode)))
	{
		if (print)
			ft_fprintf(2, "cd: not a directory: %s\n", buf);
		return (0);
	}
	return (1);
}

int		create_pwd(char *curpath, char ***environ, int free_curpath)
{
	char getcwd_path[PATH_MAX];

	if (getcwd(getcwd_path, PATH_MAX) < 0)
	{
		(free_curpath ? ft_strdel(&curpath) : (0));
		ft_error(errno, "getcwd");
		return (0);
	}
	ft_setenv("PWD", getcwd_path, 1, environ);
	return (1);
}
