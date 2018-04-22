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

int				callbase(char **av, char ***env, t_ast_node *root)
{
	pid_t		child;
	int			status;

	if ((child = fork()) < 0)
		ft_exit(errno, "fork");
	else if (!child)
	{
		if (change_fd(root) < 0)
		{
			// jc_delete_tag(root->tag_gpid);
			del_sh21_exit();
			exit(errno);
		}
		if (execve(av[0], av, *env) < 0)
		{
			// jc_delete_tag(root->tag_gpid);
			ft_exit(errno, av[0]);
		}
	}
	else
	{
		// jc_add(root->tag_gpid, child);
		// status = jc_set(root->tag_gpid, root->mod_gpid);
		child = waitpid(child, &status, WUNTRACED);
		return (status);
	}
	return (0);
}

int				try_direct_acces(char **av, char ***env, t_ast_node *root)
{
	t_sh21			*sh21;
	struct stat		st;

	sh21 = sh21_get();
	if (ft_strchr(av[0], '/') == NULL)
		return (0);
	stat(av[0], &st);
	if (S_ISDIR(st.st_mode))
		ft_error(21, av[0]);
	else
		callbase(av, env, root);
	return (1);
}

int				callsystem(char **av, char ***env, t_ast_node *root)
{
	pid_t		child;
	int			status;
	char		*str;

	str = search_bin(av[0], &sh21_get()->env);
	if ((child = fork()) < 0)
		ft_exit(errno, "fork");
	else if (!child)
	{
		if (change_fd(root) < 0)
		{
			// jc_delete_tag(root->tag_gpid);
			del_sh21_exit();
			exit(errno);
		}
		if (!str || execve(str, av, *env) < 0)
		{
			// jc_delete_tag(root->tag_gpid);
			reset_fd(root);
			ft_exit((str ? errno : -1), (str ? str : av[0]));
		}
		ft_exit((str ? errno : -1), (str ? str : av[0]));
	}
	else
	{
		// jc_add(root->tag_gpid, child);
		// status = jc_set(root->tag_gpid, root->mod_gpid);
		reset_fd(root);
		child = waitpid(child, &status, WUNTRACED);
		return (status);
	}
	return (0);
}

int 			sh21_exec_builtin(char **av, char ***env, t_ast_node *root, t_builtin builtin)
{
	pid_t		parent;
	int			status;

	if (!(root->piped_cmd || root->mod_gpid == BG))
	{
		// jc_delete_tag(root->tag_gpid);
		return (builtin.fn_ptr(arrlen(av), av, env, root));
	}
	if ((parent = fork()) < 0)
		ft_exit(errno, "fork");
	else if (!parent)
	{
		if (change_fd(root) < 0)
		{
			// jc_delete_tag(root->tag_gpid);
			del_sh21_exit();
			exit(errno);
		}
		status = builtin.fn_ptr(arrlen(av), av, env, root);
		del_sh21_exit();
		exit(status);
	}
	else
	{
		// jc_add(root->tag_gpid, parent);
		// status = jc_set(root->tag_gpid, root->mod_gpid);
		parent = waitpid(parent, &status, WUNTRACED);//SUPP
		return (status);
	}
	return (0);
}

int				sh21_exec(char **av, char ***env, t_ast_node *root)
{
	int			idx;

	idx = -1;
	if (!av[0])
		return (0);
	while (g_builtins[++idx].fn_ptr)
	{
		if (ft_strequ(av[0], g_builtins[idx].fn_name))
			return (sh21_exec_builtin(av, env, root, g_builtins[idx]));
	}
	if (try_direct_acces(av, env, root))
		return (0);
	return (callsystem(av, env, root));
}
