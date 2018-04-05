/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_call_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:30:19 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 17:16:57 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		input_call_function(t_input *input)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (g_read_function[i].key)
	{
		input->buff_len = ft_strlen(input->buff);
		if (g_read_function[i].key == input->read)
		{
			ret = g_read_function[i].call_function(input);
			input->buff_len = ft_strlen(input->buff);
			g_read_function[i].flags & CLEAR ? clear_command(input) : (0);
			g_read_function[i].flags & CLEAR ? sv_cursor(input,
				input->buff_len, input->cur_pos) : (0);
			g_read_function[i].flags & DISPLAY ? display_input(input) : (0);
			g_read_function[i].flags & RESTORE ? rt_cursor(input) : (0);
			break ;
		}
		i++;
	}
	if (!g_read_function[i].key)
		write_char(input);
	return (ret);
}
