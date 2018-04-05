/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:11:39 by hfontain          #+#    #+#             */
/*   Updated: 2018/02/20 13:27:08 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	set_cursor(int cols, int rows)
{
	tputs(tgoto(tgetstr("cm", NULL), cols, rows), 0, my_putchar);
}

void	mv_cursor(int col, int row)
{
	if (col)
		tputs(tgoto(tgetstr(col < 0 ? "le" : "nd", NULL), 0, 0), 0, my_putchar);
	if (row)
		tputs(tgoto(tgetstr(row < 0 ? "up" : "DO", NULL), 0, 0), 0, my_putchar);
}

void	sv_cursor(t_input *input, int beg, int end)
{
	beg += input->prompt_sz;
	end += input->prompt_sz;
	input->pos.x =
		(end % input->winsize.ws_col) - (beg % input->winsize.ws_col);
	input->pos.y =
		(end / input->winsize.ws_col) - (beg / input->winsize.ws_col);
}

void	rt_cursor(t_input *input)
{
	while (input->pos.y || input->pos.x)
	{
		mv_cursor(input->pos.x, input->pos.y);
		if (input->pos.x)
			input->pos.x += input->pos.x > 0 ? -1 : 1;
		if (input->pos.y)
			input->pos.y += input->pos.y > 0 ? -1 : 1;
	}
}

void	goto_end_of_prompt(t_input *input)
{
	sv_cursor(input, input->cur_pos, ft_strlen(input->buff));
	rt_cursor(input);
	my_putchar('\n');
}
