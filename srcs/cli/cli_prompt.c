/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:32:17 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/25 20:23:08 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"
#include "sh21.h"
#include "ft_printf.h"

static int	shorten_path(char **prompt, t_sh21 *sh21)
{
	int			res;
	char		*path;
	char		*home;
	size_t		home_len;

	res = 4;
	if (sh21 && (path = ft_strdup(ft_getenv("PWD", &sh21->env.orig_env))))
		res += ft_strlen(path);
	else if ((path = getcwd(NULL, MAXPATHLEN)))
		res += ft_strlen(path);
	else
		res += ft_strlen("(null)");
	home = ft_getenv("HOME", &sh21->env.orig_env);
	if (home && !ft_strncmp(path, home, (home_len = ft_strlen(home))))
	{
		*prompt = ft_strjoin("~", path + home_len);
		res = 4 + ft_strlen(*prompt);
		free(path);
	}
	else
		*prompt = path;
	return (res);
}

int			display_prompt(int last_result)
{
	char		*path;
	int			res;
	t_ft_sh		*shell;
	t_sh21		*lexer_s;

	lexer_s = sh21_get();
	shell = get_ft_shell();
	res = shorten_path(&path, lexer_s);
	exec_term_command(TC_REVERSEVIDEO);
	ft_fprintf(2, "%%");
	exec_term_command(TC_RESETGRAPHICS);
	ft_fprintf(2, "%*s\r%s%C \x1b[38;2;0;170;255m%s>{eoc} ", shell->x_size - 1,
	" ", (last_result ? ANSI_COLOR_B_RED : ANSI_COLOR_B_GREEN), 10140, path);
	free(path);
	shell->prompt_size = res;
	return (res);
}

void		prompt_select(char *prompt, int status, int heredoc)
{
	if (prompt || heredoc)
	{
		prompt = (!heredoc ? prompt : "heredoc> ");
		ft_fprintf(2, prompt);
		get_ft_shell()->prompt_size = ft_strlen(prompt);
	}
	else
		display_prompt(status);
}
