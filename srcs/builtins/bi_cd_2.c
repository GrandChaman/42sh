/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 23:56:47 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/16 23:56:49 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*cd_rule5(char *curpath, char ***environ)
{
	char				**cdpath;
	char				*buf;
	int					slash;
	int					i;

	i = -1;
	buf = NULL;
	cdpath = ft_strsplit(ft_getenv("CDPATH", environ), ':');
	while (cdpath && cdpath[++i])
	{
		slash = ft_strlen(cdpath[i]);
		if (slash > 0)
			slash--;
		buf = ft_strjoin_multiple(3, cdpath[i],
			cdpath[i][slash] == '/' ? "" : "/", curpath);
		if (ft_is_dir(buf, 0))
		{
			del_arr(&cdpath);
			return (buf);
		}
		ft_strdel(&buf);
	}
	del_arr(&cdpath);
	return (cd_rules5_2(curpath));
}

int		cd_rule8_casedotdot(int *i, char *curpath, int free_curpath)
{
	int j;

	j = *i == 0 ? 0 : -1;
	curpath[*i + 1] = 0;
	if (!ft_is_dir(curpath, 1))
	{
		(free_curpath ? ft_strdel(&curpath) : (0));
		return (0);
	}
	curpath[*i + 1] = '.';
	while (j + *i >= 0 && curpath[j + *i] != '/')
		j--;
	if (curpath[*i + 3] != '/')
		j++;
	if (j < 0)
	{
		ft_strcpy(curpath + *i + j, curpath + *i + 3);
		*i += j;
	}
	else
		ft_strcpy(curpath + 1, curpath + 3);
	return (1);
}

int		cd_rule8(char *cur, char ***environ, int flag, int free_curpath)
{
	int i;
	int len;

	i = 0;
	while (cur[i])
	{
		if (ft_strnequ(cur + i, "/./", 3) || ft_strnequ(cur + i, "/.", 3))
			ft_strcpy(cur + i, cur + i + 2);
		else if (ft_strnequ(cur + i, "//", 2))
			ft_strcpy(cur + i, cur + i + 1);
		else if (ft_strnequ(cur + i, "/../", 4)
		|| ft_strnequ(cur + i, "/..", 4))
		{
			if (!cd_rule8_casedotdot(&i, cur, free_curpath))
				return (1);
		}
		else
			i++;
	}
	if ((len = ft_strlen(cur)) > PATH_MAX || cur[0] == 0)
	{
		(free_curpath ? ft_strdel(&cur) : (0));
		return (len > PATH_MAX ? 1 : 0);
	}
	return (cd_rule10(cur, environ, flag, free_curpath));
}

int		cd_rule7(char *curpath, char ***environ, int flag, int free_curpath)
{
	const char	*pwd;
	char		*curpath_new;
	int			slash;

	if (flag == CD_P)
		return (cd_rule10(curpath, environ, flag, free_curpath));
	if (curpath[0] != '/')
	{
		if (!(pwd = ft_getenv("PWD", environ)))
			if (!create_pwd(curpath, environ, 0))
				return (1);
		pwd = ft_getenv("PWD", environ);
		slash = ft_strlen(pwd);
		(slash ? slash-- : (0));
		curpath_new = ft_strjoin_multiple(3, pwd,
			pwd[slash] == '/' ? "" : "/", curpath);
		(free_curpath ? free(curpath) : (0));
		return (cd_rule8(curpath_new, environ, flag, 1));
	}
	return (cd_rule8(curpath, environ, flag, free_curpath));
}

int		cd_rule_dash(char ***environ, int flag)
{
	char	*oldpwd;

	oldpwd = ft_strdup(ft_getenv("OLDPWD", environ));
	if (!oldpwd)
	{
		ft_error(-4, "cd");
		return (1);
	}
	if (!ft_is_dir(oldpwd, 0))
	{
		ft_strdel(&oldpwd);
		ft_error(-8, "cd");
		return (1);
	}
	return (cd_rule10((char *)oldpwd, environ, flag, 3));
}
