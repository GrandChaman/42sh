/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:57:06 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/26 16:48:40 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

int			is_env_correct(void)
{
	int		res;
	t_ft_sh	*sh;

	sh = get_ft_shell();
	res = tgetent(NULL, getenv("TERM"));
	if (res == -1 || ft_strcmp(getenv("TERM"), "xterm-256color"))
		return (!ft_fprintf(2,
			"TERM environment variable is not set or is incorrect. "
			"Works only with \"xterm-256color\"\n"));
	else if (res == 0)
		return (!ft_fprintf(2, "TERM info database not found.\n"));
	return (1);
}

void		cli_reset_cursor(t_ft_sh *sh)
{
	sh->history_pos = -1;
	sh->history_last = NULL;
	sh->prompt_size = 0;
	sh->cursor = 0;
	sh->alt_cursor = 0;
	sh->is_alt_shell = 0;
}

void		cli_loader(int destroy)
{
	t_ft_sh *shell;

	shell = get_ft_shell();
	if (destroy)
	{
		load_history(shell, 1);
		dbuf_destroy(&shell->buf);
		if (shell->autocomplete)
			ft_lstdel(&shell->autocomplete, delete_autocomplete_entry);
		shell->autocomplete_cusor = NULL;
	}
	else
	{
		signal(SIGWINCH, get_screen_size);
		get_screen_size(SIGWINCH);
		shell->history_pos = -1;
		shell->history_last = NULL;
		shell->autocomplete = NULL;
		shell->autocomplete_cusor = NULL;
		shell->history = NULL;
		shell->is_a_tty = isatty(0);
		load_history(shell, 0);
		dbuf_init(&shell->buf);
	}
}
