/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:38:41 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/19 20:38:41 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"

static int		print_exit(char ***environ)
{
	print_env(*environ);
	return (0);
}

int				bi_export(int argc,
	char **argv, char ***environ, t_ast_node *root)
{
	int		i;
	char	*var;

	(void)root;
	i = 1;
	if (argc < 2)
		return (print_exit(environ));
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			ft_putenv(ft_strdup(argv[i]), environ);
			ft_putenv(ft_strdup(argv[i]), &sh21_get()->env.local_var);
		}
		else
		{
			if ((var = ft_getenv(argv[i], &sh21_get()->env.local_var)))
				ft_setenv(argv[i], var, 1, environ);
		}
		if (ft_strnequ(argv[i], "PATH", 4))
			find_bin_paths(&sh21_get()->env, environ);
		i++;
	}
	return (0);
}
