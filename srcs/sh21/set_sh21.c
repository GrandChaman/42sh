/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sh21.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:58:39 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/19 20:38:23 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <curses.h>
#include <term.h>
#include "builtins.h"

void		reinit_term(t_sh21 *sh21)
{
	if (tcgetattr(sh21->input.tty, &sh21->terminal.term) == -1)
		ft_exit(errno, "tcgetattr");
	sh21->terminal.term.c_lflag |= ICANON;
	sh21->terminal.term.c_lflag |= ECHO;
	sh21->terminal.term.c_lflag |= ISIG;
	if (tcsetattr(sh21->input.tty, 0, &sh21->terminal.term) == -1)
		ft_exit(errno, "tcsetattr");
}

void		init_term(t_sh21 *sh21)
{
	const char	*term = getenv("TERM") ? getenv("TERM") : "xterm-256color";

	if (!(sh21->terminal.term_name = (char *)term))
		ft_exit(-5, "getenv");
	if (tcgetattr(sh21->input.tty, &sh21->terminal.term) == -1)
		ft_exit(errno, "tcgetattr");
	if (tgetent(NULL, sh21->terminal.term_name) == -1)
		ft_exit(errno, "tgetent");
	sh21->terminal.term.c_lflag &= ~(ICANON | ECHO | ISIG);
	sh21->terminal.term.c_cc[VMIN] = 1;
	sh21->terminal.term.c_cc[VTIME] = 0;
	if (tcsetattr(sh21->input.tty, TCSAFLUSH, &sh21->terminal.term) == -1)
		ft_exit(errno, "tcsetattr");
}

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
	set_debug();
	handle_windowsize(1);
	init_history(sh21);
	set_env(env, sh21);
	g_err_lex = lex_create(ERROR, NULL);
	g_end_of_input = lex_create(EOI, "End of Input");
	find_bin_paths(&sh21->env, &sh21->env.orig_env);
	sh21->terminal.isatty = isatty(0);
	return (sh21);
}

t_sh21		*sh21_get(void)
{
	static t_sh21	sh21;

	return (&sh21);
}
