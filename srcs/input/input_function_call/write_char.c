/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:29:21 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 17:47:29 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	input_putc(t_input *input, int c)
{
	input->buff = ft_strpush(input->buff, input->cur_pos, c, &input->buff_sz);
	input->cur_pos++;
	if (!((input->cur_pos + input->prompt_sz) % input->winsize.ws_col))
		my_putchar('\n');
}

int		write_char(t_input *input)
{
	char			*c;
	uint64_t		i;

	i = 0;
	clear_history(input);
	c = (char*)&input->read;
	if (input->is_select)
	{
		delete_select(input);
	}
	while (i < sizeof(input->read) && ft_isprint(c[i]))
	{
		input_putc(input, c[i]);
		input->buff_len = ft_strlen(input->buff);
		clear_command(input);
		sv_cursor(input, input->buff_len, input->cur_pos);
		display_input(input);
		rt_cursor(input);
		i++;
	}
	return (0);
}
