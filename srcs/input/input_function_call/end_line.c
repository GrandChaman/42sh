/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:28:18 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 17:16:15 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		end_line(t_input *input)
{
	while (input->cur_pos < input->buff_len - (input->is_select ? 1 : 0))
		arrow_right(input);
	return (0);
}
