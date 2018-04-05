/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:28:26 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:28:27 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		line_down(t_input *input)
{
	int i;

	i = input->winsize.ws_col;
	while (i-- && input->cur_pos < input->buff_len)
		arrow_right(input);
	return (0);
}
