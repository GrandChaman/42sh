/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:28:05 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:28:08 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		delete_back(t_input *input)
{
	if (!input->cur_pos)
		return (0);
	arrow_left(input);
	input->buff = ft_strpop(input->buff, input->cur_pos);
	input->buff_len = ft_strlen(input->buff);
	return (0);
}
