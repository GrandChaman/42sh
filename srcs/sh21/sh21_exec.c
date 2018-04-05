/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:03:18 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/19 13:16:43 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char			*search_bin(char *bin, t_env *env)
{
	int			index;
	t_hash_bin	*ret;
	char		*tmp;

	index = ft_hash(bin) % HASH_SIZE;
	ret = &env->hash_table[index];
	tmp = ft_strrchr(ret->path, '/');
	while (ret && tmp && !ft_strequ(tmp + 1, bin))
	{
		ret = ret->next;
		tmp = ret ? ft_strrchr(ret->path, '/') : NULL;
	}
	return (ret ? ret->path : NULL);
}

int				callbase(char **av, char ***env)
{
	pid_t		parent;
	int			status;

	if ((parent = fork()) < 0)
		ft_exit(errno, "callsystem");
	else if (!parent)
	{
		if (execve(av[0], av, *env) < 0)
			ft_exit(errno, av[0]);
	}
	else
	{
		parent = waitpid(parent, &status, WUNTRACED);
		return (status);
	}
	return (0);
}

int				try_direct_acces(char **av, char ***env)
{
	t_sh21			*sh21;

	sh21 = sh21_get();
	if (ft_strchr(av[0], '/') == NULL)
		return (0);
	callbase(av, env);
	return (1);
}

int				callsystem(char **av, char ***env)
{
	pid_t		parent;
	int			status;
	char		*str;

	str = search_bin(av[0], &sh21_get()->env);
	if ((parent = fork()) < 0)
		ft_exit(errno, "callsystem");
	else if (!parent)
	{
		if (str)
		{
			if (execve(str, av, *env) < 0)
				ft_exit(errno, str);
		}
		else
			ft_exit(-1, av[0]);
	}
	else
	{
		parent = waitpid(parent, &status, WUNTRACED);
		return (status);
	}
	return (0);
}

int				sh21_exec(int ac, char **av, char ***env)
{
	int			idx;

	idx = -1;
	if (!av[0])
		return (0);
	while (g_builtins[++idx].fn_ptr)
	{
		if (ft_strequ(av[0], g_builtins[idx].fn_name))
			return (g_builtins[idx].fn_ptr(ac, av, env));
	}
	if (try_direct_acces(av, env))
		return (0);
	return (callsystem(av, env));
}
