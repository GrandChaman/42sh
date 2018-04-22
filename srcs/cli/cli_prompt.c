/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:32:17 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/22 17:35:19 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"
#include "sh21.h"
#include "ft_printf.h"

int			display_prompt(int last_result)
{
	char		*path;
	int			res;
	t_ft_sh		*shell;
	t_sh21		*lexer_s;

	lexer_s = sh21_get();
	res = 4;
	jc_update_all();
	if (lexer_s && (path = ft_strdup(ft_getenv("PWD", &lexer_s->env.orig_env))))
		res += ft_strlen(path);
	else if ((path = getcwd(NULL, MAXPATHLEN)))
		res += ft_strlen(path);
	else
		res += ft_strlen("(null)");
	ft_fprintf(2, "%s%C {magenta}%s{eoc}> ",
	(last_result ? ANSI_COLOR_B_RED : ANSI_COLOR_B_GREEN), 8594, path);
	free(path);
	shell = get_ft_shell();
	shell->prompt_size = res;
	return (res);
}

void		prompt_select(char *prompt, int status, int heredoc, int fb)
{
	if (!status && fb)
		ft_fprintf(2, "{bgreen}-- OK --{eoc}\n");
	else if (fb)
	{
		if (WIFSIGNALED(status))
			ft_fprintf(2, "{bred}-- Signal : %d -- {eoc}\n", WTERMSIG(status));
		else if (WSTOPSIG(status))
			ft_fprintf(2, "{bred}-- Stopped : %d -- {eoc}\n", WSTOPSIG(status));
		else
			ft_fprintf(2, "{byellow}-- Exit : %d -- {eoc}\n",
				WEXITSTATUS(status));
	}
	if (prompt || heredoc)
	{
		prompt = (!heredoc ? prompt : "heredoc> ");
		ft_fprintf(2, prompt);
		get_ft_shell()->prompt_size = ft_strlen(prompt);
	}
	else
		display_prompt(status);
}
