/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:32:17 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/28 14:55:32 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			display_prompt(int last_result)
{
	char		*path;
	int			res;
	t_ft_sh		*shell;

	res = 4;
	if ((path = getcwd(NULL, MAXPATHLEN)))
		res += ft_strlen(path);
	else
		res += ft_strlen("(null)");
	ft_printf("%s$ {cyan}%s{eoc}> ",
	(last_result ? ANSI_COLOR_B_RED : ANSI_COLOR_B_GREEN), path);
	free(path);
	shell = get_ft_shell();
	shell->prompt_size = res;
	return (res);
}

void		prompt_select(char *prompt, int status, int heredoc, int fb)
{
	if (!status && fb)
		ft_printf("{bgreen}-- OK --{eoc}\n");
	else if (fb)
	{
		if (WIFSIGNALED(status))
			ft_printf("{bred}-- Signal : %d -- {eoc}\n", WTERMSIG(status));
		else if (WSTOPSIG(status))
			ft_printf("{bred}-- Stopped : %d -- {eoc}\n", WSTOPSIG(status));
		else
			ft_printf("{byellow}-- Exit : %d -- {eoc}\n", WEXITSTATUS(status));
	}
	if (prompt || heredoc)
	{
		prompt = (!heredoc ? prompt : "heredoc> ");
		ft_printf(prompt);
		get_ft_shell()->prompt_size = ft_strlen(prompt);
	}
	else
		display_prompt(status);
}
