/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_debugtty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <fbertoia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 16:17:10 by fbertoia          #+#    #+#             */
/*   Updated: 2018/05/11 14:06:59 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	set_debugtty(void)
{
	int		fd;

	fd = open("/dev/ttys003", O_RDWR);
	sh21_get()->debug_tty = fd;
}
