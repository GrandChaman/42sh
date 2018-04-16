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
	CD_NO_FLAG,
	CD_L,
	CD_P,
};

static char	*check_flag(int *flag, char **argv, int *error)
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
				*error = 1;
				return (NULL);
			}
		}
		i--;
		if (argv[o][i] == 'P')
			*flag = CD_P;
		if (argv[o][i] == 'L')
			*flag = CD_L;
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

int 		ft_is_dir(char *buf, int print)
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

int 		create_pwd(char *curpath, char ***environ, int free_curpath)
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

int 		cd_rule10(char *curpath, char ***environ, int flag, int free_curpath)
{
	if (chdir(curpath) < 0)
	{
		(free_curpath ? ft_strdel(&curpath) : (0));
		return (ft_error(errno, "cd"));
	}
	ft_setenv("OLDPWD", ft_getenv("PWD", environ), 1, environ);
	if (flag != CD_P)
		ft_setenv("PWD", curpath, 1, environ);
	else if (!create_pwd(curpath, environ, free_curpath))
		return (1);
	if (free_curpath == 3)
		ft_printf("%s\n", ft_getenv("PWD", environ));
	(free_curpath ? ft_strdel(&curpath) : (0));
	return (0);
}


char *cd_rule5(char *curpath, char ***environ)
{
	char				**cdpath;
	char				*buf;
	int 				slash;
	int					i;

	i = -1;
	buf = NULL;
	cdpath = ft_strsplit(ft_getenv("CDPATH", environ), ':');
	while (cdpath && cdpath[++i])
	{
		slash = ft_strlen(cdpath[i]);
		if (slash > 0)
			slash--;
		buf = ft_strjoin_multiple(3, cdpath[i], cdpath[i][slash] == '/' ? "" : "/", curpath);
		if (ft_is_dir(buf, 0))
		{
			del_arr(&cdpath);
			return (buf);
		}
		ft_strdel(&buf);
	}
	del_arr(&cdpath);
	curpath = ft_strjoin("./", curpath);
	if (!ft_is_dir(curpath, 1))
	{
		ft_strdel(&curpath);
		return (NULL);
	}
	return (curpath);
}

int			cd_rule8_casedotdot(int *i, char *curpath, int free_curpath)
{
	int j;

	j = -1;
	curpath[*i] = 0;
	if (!ft_is_dir(curpath, 1))
	{
		(free_curpath ? ft_strdel(&curpath) : (0));
		return (0);
	}
	curpath[*i] = '/';
	while (j + *i >= 0 && curpath[j + *i] != '/')
		j--;
	if (curpath[*i + 3] != '/')
		j++;
	if (j + *i != 0)
	{
		ft_strcpy(curpath + *i + j, curpath + *i + 3);
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
		if (ft_strnequ(curpath + i, "/./", 3) || ft_strnequ(curpath + i, "/.", 3))
			ft_strcpy(curpath + i, curpath + i + 2);
		else if (ft_strnequ(curpath + i, "//", 2))
			ft_strcpy(curpath + i, curpath + i + 1);
		else if ((ft_strnequ(curpath + i, "/../", 4) || ft_strnequ(curpath + i, "/..", 4)) && i != 0)
		{
			if (!cd_rule8_casedotdot(&i, curpath, free_curpath))
				return (1);
		}
		else
			i++;
	}
	if ((len = ft_strlen(curpath)) > PATH_MAX || curpath[0] == 0)
	{
		(free_curpath ? ft_strdel(&curpath) : (0));
		return (len > PATH_MAX ? 1 : 0);
	}
	return (cd_rule10(curpath, environ, flag, free_curpath));
}

int 		cd_rule7(char *curpath, char ***environ, int flag, int free_curpath)
{
	const char	*pwd;
	char				*curpath_new;
	int 				slash;

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
		curpath_new = ft_strjoin_multiple(3, pwd, pwd[slash] == '/' ? "" : "/", curpath);
		(free_curpath ? free(curpath) : (0));
		return (cd_rule8(curpath_new, environ, flag, 1));
	}
	return (cd_rule8(curpath, environ, flag, free_curpath));
}

int 		cd_rule_dash(char ***environ, int flag)
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

int			bi_cd(int argc, char **argv, char ***environ)
{
	char				*curpath;
	int					flag;
	int					error;

	error = 0;
	(void)argc;
	flag = 0;
	curpath = check_flag(&flag, argv, &error);
	ft_printf("lala curpath = %s\n", )
	if (error)
		return (1);
	if (!curpath)
		return (go_home(environ) != 0);
	if (ft_strequ(curpath, "-"))
	{
		return (cd_rule_dash(environ, flag));
	}
	if (curpath[0] == '/' || curpath[0] == '.')
		return (cd_rule7(curpath, environ, flag, 0));
	else if (!(curpath = cd_rule5(curpath, environ)))
		return (1);
	else
		return (cd_rule7(curpath, environ, flag, 1));
}


//cd -
// cd (-P|-L) dossier_non_droit
