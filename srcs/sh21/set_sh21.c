/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sh21.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:58:39 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/19 15:46:26 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <curses.h>
#include <term.h>
#include "builtins.h"

void		set_env(char **env, t_sh21 *sh21)
{
	int		shlvl;
	char	*strlvl;

	sh21->env.orig_env = cpy_arr(env);
	shlvl = ft_atoi(ft_getenv("SHLVL", &sh21->env.orig_env)
	? ft_getenv("SHLVL", &sh21->env.orig_env) : "0") + 1;
	strlvl = ft_itoa(shlvl);
	ft_setenv("SHLVL", strlvl, 1, &sh21->env.orig_env);
	ft_strdel(&strlvl);
	if (!ft_getenv("TERM", &sh21->env.orig_env))
		ft_setenv("TERM", "xterm-256color", 1, &sh21->env.orig_env);
	if (!ft_getenv("PATH", &sh21->env.orig_env))
		ft_setenv("PATH", "/bin:/usr/bin", 1, &sh21->env.orig_env);
}

t_sh21		*sh21_init(char *env[])
{
	t_sh21	*sh21;

	sh21 = sh21_get();
	set_env(env, sh21);
	g_err_lex = lex_create(ERROR, NULL);
	g_end_of_input = lex_create(EOI, "End of Input");
	find_bin_paths(&sh21->env, &sh21->env.orig_env);
	sh21->terminal.isatty = isatty(0);
	set_debugtty();
	return (sh21);
}

t_sh21		*sh21_get(void)
{
	static t_sh21	sh21[16];

	return (&sh21[g_shell_idx]);
}
