/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:55:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/21 19:07:25 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

void		execute_touch(t_ft_sh *shell, unsigned long rchar)
{
	unsigned int	i;
	char			str_part;
	void			(*f)(unsigned long);

	i = 0;
	cancel_selection(shell, rchar);
	cancel_autocompletion(shell, rchar);
	if ((f = g_special_char_f(rchar)))
		f(rchar);
	else
		while (rchar && i < sizeof(unsigned long))
		{
			str_part = (rchar << (sizeof(unsigned long) - ((i + 1) * 8)))
				>> (sizeof(unsigned long) - ((i + 1) * 8));
			rchar >>= 8;
			i++;
			if (ft_isprint(str_part))
				print_normal_touch(shell, str_part);
			else if (str_part != '\n')
				break ;
		}
}

static int	read_command_routine(t_ft_sh *sh)
{
	unsigned long	rchar;
	int				rvalue;
	unsigned char	tmp[8];

	rchar = 0;
	rvalue = 1;
	sh = get_ft_shell();
	ft_bzero(tmp, 8);
	while (42)
	{
		rvalue = read(0, tmp, 8);
		if (rvalue == -1 || (tmp[0] == '\n' && !sh->autocomplete_cusor)
		|| (tmp[0] == T_CTRL_D && !sh->buf.cursor)
		|| tmp[0] == T_CTRL_C)
			break ;
		rchar = *((unsigned long*)tmp);
		execute_touch(get_ft_shell(), rchar);
		ft_bzero(tmp, 8);
	}
	cancel_selection(sh, rchar);
	while (sh->cursor < sh->buf.cursor)
		move_in_terminal(T_RARR);
	cancel_autocompletion(sh, '\0');
	(tmp[0] == T_CTRL_D || tmp[0] == T_CTRL_C ? dbuf_clear(&sh->buf) : 0);
	return (tmp[0]);
}

static char	*read_command_outro(t_ft_sh *sh, char lchar, int heredoc)
{
	char *res;

	while (sh->cursor < sh->buf.cursor)
		move_in_terminal(T_RARR);
	ft_putchar('\n');
	if (lchar == T_CTRL_C)
		dbuf_clear(&sh->buf);
	if ((lchar == T_CTRL_D && !heredoc && !sh->buf.cursor)
		|| (lchar == T_CTRL_C && heredoc))
		res = NULL;
	else if (lchar == T_CTRL_D && heredoc)
	{
		res = ft_strnew(1);
		res[0] = T_CTRL_D;
	}
	else
		res = ft_strdup(sh->buf.buf);
	sh->cursor = 0;
	sh->alt_cursor = 0;
	ft_free((void**)&sh->history_last);
	dbuf_clear(&sh->buf);
	apply_terminal_setting(1);
	free(sh->select);
	return (res);
}

char		*read_command(char *prompt, int status, int heredoc)
{
	char	*nprompt;
	t_ft_sh	*sh;
	char	lchar;

	sh = get_ft_shell();
	prompt_select(prompt, status, heredoc);
	sh->is_alt_shell = (prompt || heredoc ? 1 : 0);
	apply_terminal_setting(0);
	lchar = read_command_routine(sh);
	if (lchar != T_CTRL_D &&
		!heredoc && (nprompt = check_correct(get_ft_shell()->buf.buf)))
	{
		sh->cursor = sh->buf.cursor;
		sh->alt_cursor = sh->cursor + 1;
		dbuf_insert(&sh->buf, sh->cursor++, '\n');
		ft_putchar('\n');
		apply_terminal_setting(1);
		return (read_command(nprompt, status, 0));
	}
	return (read_command_outro(sh, lchar, heredoc));
}
