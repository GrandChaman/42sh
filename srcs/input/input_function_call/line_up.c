/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:28:30 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:28:33 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		line_up(t_input *input)
{
	int i;

	i = 0;
	while (i++ < input->winsize.ws_col && input->cur_pos)
		arrow_left(input);
	return (0);
}
