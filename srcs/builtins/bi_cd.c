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

static char *ft_work_on_it(char *str)
{
	int i;
	int o;
	char *result;

	result = NULL;
	i = 0;
	o = 0;
	while (str[i])
	{
		if (str[i] == '/')
			o = i + 1;
		i++;
	}
	result = ft_memalloc(sizeof(char ) * o);
	ft_printf("str = %s\n", str);
	ft_strncpy(result, str, o);
	ft_printf("result = %s\n", result);
	return (result);
}

static char *change_path(int *error, char **argv, char ***environ, t_flag *flag)
{
	char cwd[1024];
	char *str;	

	flag->buf_to_free = 0;
	if (flag->flag_P)
	{
		if (!argv[flag->idx])
		{
			if (go_home(environ) == -3)
				*error = 1;
			return (NULL);
		}
		return (argv[flag->idx]);
	}
	if (flag->flag_L || (flag->flag_L == 0 && flag->flag_P == 0))
	{
		if (ft_strcmp(argv[flag->idx], "..") == 0)
		{
   			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				str = ft_getenv("PWD", environ);
				str = ft_work_on_it(str);
				flag->buf_to_free = 1;
			   return (str);
			}
   			else
			   perror("getcwd() error");
		}
	}
	return (argv[flag->idx]);
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

static int	check_flag(t_flag *flag, char **argv)
{
	int i;
	int o;

	o = 1;
	flag->flag_L = 0;
	flag->flag_P = 0;
	while (argv[o] && argv[o][0] == '-')
	{
		i = 1;		
		if (!argv[o][1])
			return (o);
		while (argv[o][i])
		{
			if (argv[o][i] != 'L' && argv[o][i] != 'P')
			{
				ft_printf("42sh :cd: -%c: invalid option\n");
				ft_printf("cd: usage: cd [-L|-P] [dir]\n");
				return (-1);
			}
			i++;
		}
		i--;
		if (argv[o][i] == 'P')
		{
			flag->flag_P = 1;
			flag->flag_L = 0;
		}
		if (argv[o][i] == 'L')
		{
			flag->flag_L = 1;
			flag->flag_P = 0;
		}
		o++;
	}
	return (o);
}

int			bi_cd(int argc, char **argv, char ***environ)
{
	const char		*oldpwd = ft_getenv("OLDPWD", environ);
	char			*buf;
	int				error;
	t_flag			flag;
	

	if (argc < 2)
		return (go_home(environ) != 0); // {AS super si home == /tmp}
	if ((flag.idx = check_flag(&flag, argv)) == -1)
		return (-1);
	if ((buf = change_path(&error, argv, environ, &flag)) == NULL)
	{
		if (error)
			return (-1);
		return (1);
	}
	if (ft_strequ(buf, "-"))
	{
		if (!oldpwd)
			return (ft_error(-7, "cd"));
		if (!chdir(oldpwd))
			return (change_oldpwd_pwd(environ, NULL));
		return (ft_error(-4, "cd"));
	}
	if (chdir(buf) == 0)
	{
		change_oldpwd_pwd(environ, buf);
		if (flag.buf_to_free)
			free(buf);
		return (0);
	}
	else
		return (ft_error(errno, "cd"));
}
//Reste a checker si les valeurs de retours sont bonnes
//	 +  les protections !!! + rajouter un / si on fait cd / puis cd tmp !!!!!!!!!!!!!!!!!!!!!!!!!