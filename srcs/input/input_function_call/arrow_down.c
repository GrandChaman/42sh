/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_down.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:27:19 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:27:20 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			arrow_down(t_input *input)
{
	if (input->is_select || !input->history.needle)
		return (0);
	else if (input->history.needle)
		input->history.needle = input->history.needle->previous;
	if (input->history.needle || input->historic_buff)
	{
		clear_command(input);
		ft_strdel(&input->buff);
		input->buff = ft_strdup(input->history.needle ?
			input->history.needle->command : input->historic_buff);
		input->buff_len = ft_strlen(input->buff);
		input->buff_sz = input->buff_len;
		input->cur_pos = input->buff_len;
		display_input(input);
	}
	return (0);
}
