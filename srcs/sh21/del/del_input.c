/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:50:57 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 14:50:59 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		del_input(t_input *input)
{
	if (!input)
		return ;
	ft_strdel(&(input->prompt));
	ft_strdel(&(input->buff));
	ft_strdel(&(input->clipboard));
	ft_strdel(&sh21_get()->input.historic_buff);
}
