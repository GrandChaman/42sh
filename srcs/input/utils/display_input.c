/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:30:13 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/13 13:58:51 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	display_input(t_input *input)
{
	int i;

	i = 0;
	if (!input->is_select)
		tputs(tgetstr("me", NULL), 1, my_putchar);
	show_prompt(input);
	while (i < (int)input->buff_len)
	{
		if (input->start_select >= 0 && i == input->start_select)
			tputs(tgetstr("mr", NULL), 1, my_putchar);
		if (input->end_select >= 0 && i == input->end_select + 1)
			tputs(tgetstr("me", NULL), 1, my_putchar);
		ft_putchar_fd(input->buff[i++], input->tty);
	}
	tputs(tgetstr("me", NULL), 1, my_putchar);
	if (((input->prompt_sz + input->buff_len) % input->winsize.ws_col) == 0)
		my_putchar('\n');
}
