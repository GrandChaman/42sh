/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_debugtty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 16:17:10 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/13 16:17:19 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	set_debugtty(void)
{
	int fd;

	fd = open("/dev/ttys001", O_WRONLY);
	ft_printf("debug_ttys001\n", fd);
	sh21_get()->debug_tty = fd;
}
