/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_left.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:27:28 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 14:00:39 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		arrow_left(t_input *input)
{
	if (input->cur_pos < 1)
		return (0);
	sv_cursor(input, input->cur_pos, input->cur_pos - 1);
	if (input->is_select)
	{
		if (input->last_mv >= (int)input->cur_pos)
		{
			input->start_select--;
		}
		else
		{
			input->end_select--;
		}
	}
	--input->cur_pos;
	rt_cursor(input);
	return (0);
}
