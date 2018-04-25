/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:44:02 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/19 20:37:40 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"

int		bi_setenv(int argc, char **argv, char ***environ, t_ast_node *root)
{
	char	**args;
	int		err;

	(void)root;
	if (argc == 1)
		return (bi_env(1, argv, environ, root));
	else
	{
		args = ft_strsplit(argv[1], '=');
		err = ft_setenv(args[0], args[1], 1, environ);
		if (ft_strnequ(args[0], "PATH", 4))
			find_bin_paths(&sh21_get()->env, environ);
		del_arr(&args);
	}
	return (err);
}
