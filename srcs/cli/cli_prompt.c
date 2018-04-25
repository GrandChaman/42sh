/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:32:17 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/25 13:11:22 by fle-roy          ###   ########.fr       */
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
	shell = get_ft_shell();
	res = 4;
	if (lexer_s && (path = ft_strdup(ft_getenv("PWD", &lexer_s->env.orig_env))))
		res += ft_strlen(path);
	else if ((path = getcwd(NULL, MAXPATHLEN)))
		res += ft_strlen(path);
	else
		res += ft_strlen("(null)");
	exec_term_command(TC_REVERSEVIDEO);
	ft_fprintf(2, "%%");
	exec_term_command(TC_RESETGRAPHICS);
	ft_fprintf(2, "%*s\r%s%C {bmagenta}%s{eoc}> ", shell->x_size - 1, " ",
	(last_result ? ANSI_COLOR_B_RED : ANSI_COLOR_B_GREEN), 10140 , path);
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
