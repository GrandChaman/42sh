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

int				callsystem(char *cmd, char **av, char ***env, t_ast_node *root)
{
	pid_t		child;
	int			status;

	status = 0;
	if ((child = fork()) < 0)
		ft_exit(errno, "fork");
	else if (!child)
	{
		if (change_fd(root) < 0)
		{
			del_sh21_exit();
			exit(errno);
		}
		if (!cmd || execve(cmd, av, *env) < 0)
			ft_exit((cmd ? errno : -1), (cmd ? cmd : av[0]));
		ft_exit((cmd ? errno : -1), (cmd ? cmd : av[0]));
	}
	else
	{
		jc_add(root->tag_gpid, child, jc_cmd(root));
		reset_fd(root);
		if (!root->piped_cmd)
			status = jc_set(root->tag_gpid, root->mod_gpid);
		return (status);
	}
	return (0);
}


int				try_direct_acces(char **av, char ***env, t_ast_node *root)
{
	t_sh21			*sh21;
	struct stat		st;
	char 			*cmd;

	sh21 = sh21_get();
	if (ft_strchr(av[0], '/') != NULL)
	{
		stat(av[0], &st);
		if (S_ISDIR(st.st_mode))
			return (ft_error(21, av[0]));
		else
			return (callsystem(av[0], av, env, root));
	}
	else
	{
		cmd = search_bin(av[0], &sh21_get()->env);
		return (callsystem(cmd, av, env, root));
	}
}

int 			sh21_exec_builtin(char **av, char ***env, t_ast_node *root, t_builtin builtin)
{
	pid_t		parent;
	int			status;

	status = 0;
	if (!(root->piped_cmd || root->mod_gpid == BG)) 
	{ 
	  jc_delete_tag(root->tag_gpid); 
	  return (builtin.fn_ptr(arrlen(av), av, env, root)); 
	}
	if ((parent = fork()) < 0)
		ft_exit(errno, "fork");
	else if (!parent)
	{
		if ((status = change_fd(root)) >= 0)
			status = builtin.fn_ptr(arrlen(av), av, env, root);
		del_sh21_exit();
		exit(status);
	}
	else
	{
		reset_fd(root);
		jc_add(root->tag_gpid, parent, jc_cmd(root));
		if (!root->piped_cmd)
			status = jc_set(root->tag_gpid, root->mod_gpid);
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
	return (try_direct_acces(av, env, root));
}
