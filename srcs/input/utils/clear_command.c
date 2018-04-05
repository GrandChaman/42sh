/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:30:02 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:30:05 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	clear_command(t_input *input)
{
	int nb_up;

	input->cur_pos += input->prompt_sz;
	nb_up = input->cur_pos / input->winsize.ws_col;
	if (nb_up > 0)
		tputs(tgoto(tgetstr("UP", NULL), 0, nb_up), 1, my_putchar);
	tputs(tgoto(tgetstr("DL", NULL), 0, 1 + (ft_strlen(input->prompt) +
		ft_strlen(input->buff)) / input->winsize.ws_col), 1, my_putchar);
	tputs((tgetstr("cr", NULL)), 1, my_putchar);
	input->cur_pos -= input->prompt_sz;
}
