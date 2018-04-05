/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_beg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:29:04 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:29:05 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		word_beg(t_input *input)
{
	arrow_left(input);
	while (input->buff[input->cur_pos] == ' ')
		arrow_left(input);
	while (input->cur_pos)
	{
		arrow_left(input);
		if (input->cur_pos > 0 && input->buff[input->cur_pos - 1] == ' ')
			break ;
	}
	return (0);
}
