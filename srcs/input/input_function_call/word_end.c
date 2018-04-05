/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:29:13 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:29:14 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		word_end(t_input *input)
{
	arrow_right(input);
	while (input->buff[input->cur_pos] == ' '
		&& input->cur_pos < input->buff_len - (input->is_select ? 1 : 0))
		arrow_right(input);
	while (input->cur_pos < input->buff_len - (input->is_select ? 1 : 0))
	{
		arrow_right(input);
		if (input->buff[input->cur_pos] == ' ')
			break ;
	}
	return (0);
}
