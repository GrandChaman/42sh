/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_right.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:27:37 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 14:00:47 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			arrow_right(t_input *input)
{
	if (input->cur_pos >= input->buff_len - input->is_select)
		return (0);
	sv_cursor(input, input->cur_pos, input->cur_pos + 1);
	if (input->is_select)
	{
		if (input->last_mv <= (int)input->cur_pos)
		{
			input->end_select++;
		}
		else
		{
			input->start_select++;
		}
	}
	++input->cur_pos;
	rt_cursor(input);
	return (0);
}
