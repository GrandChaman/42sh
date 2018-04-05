/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opentty.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:30:50 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:30:51 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	opentty(t_input *input)
{
	if ((input->tty = open("/dev/tty", O_RDWR)) < 0)
		ft_exit(errno, "open");
	if (!(isatty(input->tty)))
		ft_exit(errno, "isatty");
}
