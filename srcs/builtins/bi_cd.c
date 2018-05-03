/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:45:16 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/18 18:48:22 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void			assign_flag(int *i, int *o, int *flag, char **argv)
{
	*i = *i - 1;
	if (argv[*o][*i] == 'P')
		*flag = CD_P;
	if (argv[*o][*i] == 'L')
		*flag = CD_L;
	*o = *o + 1;
}

static char			*check_flag(int *flag, char **argv, int *error)
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
					"cd: -%c: invalid option\nusage:"
					" cd [-L|-P] [dir]\n");
				*error = 1;
				return (NULL);
			}
		}
		assign_flag(&i, &o, flag, argv);
	}
	return (argv[o]);
}

int					cd_rule10(char *curpath, char ***environ,
	int flag, int free_curpath)
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

int					bi_cd(int argc, char **argv,
	char ***environ, t_ast_node *root)
{
	char				*curpath;
	int					flag;
	int					error;

	error = 0;
	(void)argc;
	(void)root;
	flag = 0;
	curpath = check_flag(&flag, argv, &error);
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
