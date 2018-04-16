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

enum flag_cd {
	CD_NO_FLAG;
	CD_L;
	CD_P;
}

static char	*check_flag(int *flag, char **argv)
{
	int i;
	int o;

	o = 1;
	while (argv[o] && argv[o][0] == '-')
	{
		i = 0;
		if (!argv[o][1])
			return (argv[o]);
		while (argv[o][++i])
		{
			if (argv[o][i] != 'L' && argv[o][i] != 'P')
			{
				ft_fprintf(2,
					"42sh :cd: -%c: invalid option\ncd: usage: cd [-L|-P] [dir]\n");
				return (NULL);
			}
		}
		i--;
		if (argv[o][i] == 'P')
			flag = CD_P;
		if (argv[o][i] == 'L')
			flag = CD_L;
		o++;
	}
	return (argv[o]);
}

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

int 		go_home(char ***environ)
{
	const char		*home = ft_getenv("HOME", environ);

	if (!chdir(home)) // PAS BON SI HOME == /tmp
		return (change_oldpwd_pwd(environ, NULL));
	return (ft_error(-3, "cd"));
}

int 		is_dir(*buf)
{
	struct stat file_stat;

	if (lstat(*buf, &file_stat) < 0)
	{
		ft_error(errno, "cd");
		return (0);
	}
	if (!S_IFDIR(file_stat.st_mode))
	{
		ft_strdel(*buf);
		ft_fprintf(2, "cd: not a directory: %s\n", curpath);
		return (0);
	}
	return (1);
}

char *cd_rule5(char *curpath, char ***environ)
{
	char				**cdpath;
	char				*buf;
	int 				slash;
	int					i;

	i = -1;
	buf = NULL;
	cdpath = ft_strplit(ft_getenv("CDPATH", environ), ':');
	while (cdpath && cdpath[++i])
	{
		slash = ft_strlen(cdpath[i]);
		if (slash > 0)
			slash--;
		buf = ft_strjoin_multiple(3, cdpath[i], cdpath[i][slash] == '/' ? "" : "/", curpath);
		if (lstat(buf, &file_stat) >= 0 && S_IFDIR(file_stat.st_mode))
		{
			del_arr(&cdpath);
			return (buf);
		}
		ft_strdel(buf);
	}
	del_arr(&cdpath);
	*buf = ft_strjoin("./", curpath);
	if (!is_dir(buf))
	{
		ft_strdel(buf);
		return (1);
	}
	return (buf);
}

int 		cd_rule7(char *curpath, char ***environ, int flag, int free_curpath)
{
	const char	*oldpwd = ft_getenv("OLDPWD", environ);
	const char	*pwd;
	char				*curpath_new;
	int 				slash;

	if (flag == CD_P)
		return (cd_rule10());
	if (curpath[0] != '/')
	{
		pwd = ft_getenv("PWD", environ);
		slash = ft_strlen(pwd);
		(slash ? slash-- : (0));
		curpath_new = ft_strjoin_multiple(3, pwd, pwd[slash] == '/' ? "" : "/", curpath);
		free(pwd);
		(free_curpath ? free(curpath) : (0));
		return (cd_rule8(curpath_new, environ, flag, 1));
	}
	return (cd_rule8(curpath, environ, flag, free_curpath));
}



int			cd_rule8_casedotdot(int *i, char *curpath, int free_curpath)
{
	int j;

	j = -1;
	curpath[*i] = 0;
	if (!is_dir(buf))
	{
		(free_curpath ? ft_strdel(curpath) : (0));
		return (0);
	}
	curpath[*i] = '/';
	while (j + *i >= 0 && curpath[j + *i] != '/')
		j--;
	if (j + *i != 0)
	{
		ft_strcpy(curpath + *i + j, curpath + *i);
		*i += j;
	}
	return (1);
}

int 		cd_rule8(char *curpath, char ***environ, int flag, int free_curpath)
{
	int i;
	int len;

	i = 0;
	while (curpath[i])
	{
		if (ft_strnequ(curpath + i, "/./", 3))
			ft_strcpy(curpath + i, curpath + i + 2);
		else if (ft_strnequ(curpath + i, "//", 2))
			ft_strcpy(curpath + i, curpath + i + 1);
		else if (ft_strnequ(curpath + i, "/../", 4) && i != 0)
			if (!cd_rule8_casedotdot(&i, curpath, free_curpath))
				return (1);
		else
			i++;
	}
	if (curpath[0] == 0 || (len == ft_strlen(curpath)) > PATH_MAX)
	{
		(free_curpath ? ft_strdel(curpath) : (0));
		return (len > PATH_MAX ? 1 : 0);
	}
	return (cd_rule10(curpath, environ, flag, free_curpath));
}

int 		cd_rule10(char *curpath, char ***environ, int flag, int free_curpath)
{
	char getcwd_path[PATH_MAX];

	if (chdir(curpath) < 0)
	{
		(free_curpath ? ft_strdel(curpath) : (0));
		return (ft_error(errno, "cd"));
	}
	ft_setenv("OLDPWD", ft_getenv("PWD", environ), 1, environ);
	if (flag != CD_P)
		ft_setenv("PWD", curpath, 1, environ);
	else
	{
		if (getcwd(getcwd_path, PATH_MAX) < 0)
		{
			(free_curpath ? ft_strdel(curpath) : (0));
			return (ft_error(errno, "getcwd"));
		}
		ft_setenv("PWD", getcwd_path, 1, environ);
	}
	return (0);
}

int 		cd_rule_dash(char *curpath, char ***environ, int flag, int free_curpath)
{
	int		go_oldpwd;

	if ()
}

int			bi_cd(int argc, char **argv, char ***environ)
{
	char				*curpath;
	int					flag;

	flag = 0;
	if (!(curpath = check_flag(&flag, argv)))
		return (1);
	if (!curpath)
		return (go_home(environ) != 0); // {AS super si home == /tmp}
	if (ft_strequ(curpath, "-"))
		return (cd_rule_dash(curpath, environ, flag, 0));
	if (curpath[0] == '/' || curpath[0] == '.')
		return (cd_rule7(curpath, environ, flag, 0)); // proceed to step 7
	else if (!(curpath = cd_rule5(curpath, environ)))
		return (1);
	else
		return (cd_rule7(curpath, environ, flag, 1));
}
