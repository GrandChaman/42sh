/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:24:58 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/22 13:11:58 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

void					insert_in_cli(char *str)
{
	t_ft_sh *sh;
	int		i;

	sh = get_ft_shell();
	i = 0;
	while (str[i])
		print_normal_touch(sh, str[i++]);
}

void					sh_clear_screen(unsigned long rchar)
{
	t_ft_sh *sh;

	(void)rchar;
	sh = get_ft_shell();
	dbuf_clear(&sh->buf);
	cli_reset_cursor(sh);
	exec_term_command(TC_CLEAR);
	display_prompt(0);
}

static void				cursor_repositionning(t_ft_sh *sh, int ncur,
		int ocur, int is_del)
{
	int has_print_a_nl;

	has_print_a_nl = ((sh->buf.cursor + sh->prompt_size) % sh->x_size == 0);
	if (is_del && has_print_a_nl)
		ft_putchar(' ');
	if (is_del)
		exec_term_command(TC_RESETCURPOS);
	else
	{
		if (has_print_a_nl)
		{
			exec_term_command(TC_MOVEUP);
			exec_term_command_p(TC_MOVENRIGHT, 0, sh->x_size);
		}
		sh->cursor = --ncur;
		exec_term_command(TC_MOVELEFT);
		while (--ncur > ocur)
			move_in_terminal(T_LARR);
		if (has_print_a_nl)
			exec_term_command(TC_MOVERIGHT);
	}
}

void					update_stdout(t_ft_sh *sh, int isdel)
{
	int len;
	int tmp;
	int ncur;
	int ocur;

	len = (sh->buf.cursor - sh->cursor);
	ncur = sh->cursor + isdel;
	ocur = ncur;
	if (isdel)
		exec_term_command(TC_SAVECURPOS);
	while (len > 0)
	{
		tmp = ((sh->x_size) - ((sh->prompt_size + ncur) % sh->x_size)) + isdel;
		tmp = (tmp > len + isdel ? len + isdel : tmp);
		ft_printf("%*s", tmp, " ");
		exec_term_command_p(TC_MOVENLEFT, 0, tmp);
		exec_term_command_p(TC_INSERTNCHAR, 0, tmp);
		write(1, (sh->buf.buf + ncur - isdel), tmp);
		len -= tmp;
		ncur += tmp;
		if ((isdel && len >= 0) || (!isdel && (len > 0
			|| (sh->buf.cursor + sh->prompt_size) % sh->x_size == 0)))
			ft_putchar('\n');
	}
	cursor_repositionning(sh, ncur, ocur, isdel);
}

void					(*g_special_char_f(unsigned long val))(unsigned long)
{
	int i;

	i = -1;
	while (g_ft_touch_list[++i].touch)
		if (g_ft_touch_list[i].touch == val)
			return (g_ft_touch_list[i].f);
	return (NULL);
}
