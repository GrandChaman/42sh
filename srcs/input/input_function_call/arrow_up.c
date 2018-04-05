/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:27:44 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:27:47 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			arrow_up(t_input *input)
{
	if (input->is_select)
		return (0);
	if (!input->history.needle)
	{
		input->history.needle = input->history.list;
		if (!input->historic_buff)
			input->historic_buff = ft_strdup(input->buff);
	}
	else if (input->history.needle && input->history.needle->next)
		input->history.needle = input->history.needle->next;
	if (input->history.needle)
	{
		clear_command(input);
		ft_strdel(&input->buff);
		input->buff = ft_strdup(input->history.needle->command);
		input->buff_len = ft_strlen(input->history.needle->command);
		input->buff_sz = input->buff_len;
		input->cur_pos = input->buff_len;
		display_input(input);
	}
	return (0);
}
