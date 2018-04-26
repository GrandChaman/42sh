/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <fbertoia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:03:18 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/22 16:12:17 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char			*search_bin(char *bin, t_env *env)
{
	int			index;
	t_hash_bin	*ret;
	char		*tmp;

	index = ft_hash(bin) % (HASH_SIZE);
	ret = &env->hash_table[index];
	tmp = ft_strrchr_2(ret->path, '/');
	while (ret && tmp && !ft_strequ(tmp + 1, bin))
	{
		ret = ret->next;
		tmp = ret ? ft_strrchr(ret->path, '/') : NULL;
	}
	return (ret ? ret->path : NULL);
}

int				try_direct_acces(char **av, char ***env, t_ast_node *root)
{
	t_sh21			*sh21;
	struct stat		st;
	char			*cmd;

	sh21 = sh21_get();
	if (ft_strchr(av[0], '/') != NULL)
	{
		if (stat(av[0], &st) > 0 && S_ISDIR(st.st_mode))
		{
			jc_delete_tag(root->tag_gpid);
			return (ft_error(21, av[0]));
		}
		else
			return (callsystem(av[0], av, env, root));
	}
	else
	{
		cmd = search_bin(av[0], &sh21_get()->env);
		return (callsystem(cmd, av, env, root));
	}
}

int				sh21_exec(char **av, char ***env, t_ast_node *root)
{
	int			idx;

	idx = -1;
	if (!av[0])
	{
		jc_delete_tag(root->tag_gpid);
		return (0);
	}
	while (g_builtins[++idx].fn_ptr)
	{
		if (ft_strequ(av[0], g_builtins[idx].fn_name))
			return (sh21_exec_builtin(av, env, root, g_builtins[idx]));
	}
	return (try_direct_acces(av, env, root));
}
