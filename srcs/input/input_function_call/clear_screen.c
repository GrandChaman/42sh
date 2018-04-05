/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:27:55 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:27:58 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		sh21_clear_screen(t_input *input)
{
	tputs(tgoto(tgetstr("cl", NULL), 0, 0), 1, my_putchar);
	input->cur_pos = 0;
	input->buff_len = 0;
	input->start_select = -1;
	input->end_select = -1;
	input->is_select = 0;
	if (input->buff)
		ft_memdel((void**)&input->buff);
	input->buff = ft_strnew(BUFF_SIZE_INPUT_21SH);
	input->buff_sz = BUFF_SIZE_INPUT_21SH;
	clear_history(input);
	input->in = 1;
	input->history.needle = NULL;
	input->last_mv = 0;
	ft_strdel(&input->clipboard);
	show_prompt(input);
	return (0);
}
