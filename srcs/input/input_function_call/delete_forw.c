/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_forw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:28:13 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:28:16 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		delete_forw(t_input *input)
{
	input->buff = ft_strpop(input->buff, input->cur_pos);
	input->buff_len = ft_strlen(input->buff);
	return (0);
}
