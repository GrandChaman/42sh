/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:25:53 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/19 20:16:31 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"
#include "builtins.h"
#include "env.h"

static	int		flag_i(char **av, char ***cpy_env, int *i)
{
	del_arr(cpy_env);
	if (!av[++(*i)])
		return (0);
	return (2);
}

static	int		flag_u(char **av, char ***cpy_env, int *i)
{
	if (av[++(*i)])
	{
		ft_unsetenv(av[(*i)++], cpy_env);
		if (!av[*i])
			return (print_env(*cpy_env));
	}
	else
		return (env_usage('u', 2));
	return (2);
}

static	int		flag_equal(char **av, char ***cpy_env, int *i)
{
	int a;

	a = ft_strindex(av[*i], '=');
	if (av[*i][0] == '=')
		return (ft_error((errno = EINVAL), av[0]));
	else
	{
		av[*i][a] = '\0';
		ft_setenv((av[*i]), (av[*i] + a + 1), (1), cpy_env);
	}
	if (!av[++(*i)])
		return (print_env(*cpy_env));
	return (2);
}

int				bi_env(int ac, char *av[], char ***environ, t_ast_node *root)
{
	int		i;
	int		ret;
	char	**tmp;
	t_env	*env;

	(void)ac;
	if ((i = 1) && !av[i])
		return (print_env(*environ));
	env = &sh21_get()->env;
	tmp = cpy_arr(*environ);
	del_arr(&env->env_cpy);
	env->env_cpy = tmp;
	if (av[i] && ft_strequ(av[i], "-i"))
		if ((ret = flag_i(av, &env->env_cpy, &i)) < 2)
			return (ret);
	while (av[i] && ft_strequ(av[i], "-u"))
		if ((ret = flag_u(av, &env->env_cpy, &i)) < 2)
			return (ret);
	while (av[i] && (ft_strindex(av[i], '=')) >= 0)
		if ((ret = flag_equal(av, &env->env_cpy, &i)) < 2)
			return (ret);
	return (sh21_exec(av + i, &env->env_cpy, root));
}
