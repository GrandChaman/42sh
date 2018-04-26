/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21_exec_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:58:44 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/26 14:58:46 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int		failed_fork(t_ast_node *root)
{
	jc_delete_tag(root->tag_gpid);
	ft_exit(errno, "fork");
}

static int		sh21_exec_father(t_ast_node *root, pid_t parent)
{
	int status;

	status = 0;
	reset_fd(root);
	jc_add(root->tag_gpid, parent, jc_cmd(root));
	if (!root->piped_cmd)
		status = jc_set(root->tag_gpid, root->mod_gpid);
	return (status);
}

int				callsystem(char *cmd, char **av, char ***env, t_ast_node *root)
{
	pid_t		child;
	int			status;

	status = 0;
	if ((child = fork()) < 0)
		failed_fork(root);
	else if (!child)
	{
		assign_var(root);
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
		return (sh21_exec_father(root, parent));
	return (0);
}

int				sh21_exec_builtin(char **av, char ***env,
				t_ast_node *root, t_builtin builtin)
{
	pid_t		parent;
	int			status;

	status = 0;
	if (!ft_strequ(builtin.fn_name, "env")
		&& !(root->piped_cmd || root->mod_gpid == BG))
	{
		jc_delete_tag(root->tag_gpid);
		return (builtin.fn_ptr(arrlen(av), av, env, root));
	}
	if ((parent = fork()) < 0)
		failed_fork(root);
	else if (!parent)
	{
		assign_var(root);
		if ((status = change_fd(root)) >= 0)
			status = builtin.fn_ptr(arrlen(av), av, env, root);
		del_sh21_exit();
		exit(status);
	}
	else
		return (sh21_exec_father(root, parent));
	return (0);
}