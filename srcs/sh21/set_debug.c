/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 18:32:54 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/14 22:00:22 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	set_debug(void)
{
	t_sh21 *sh21;

	sh21 = sh21_get();
	sh21->debug_tty = open("/dev/ttys002", O_RDWR);
	sh21->input.debug_tty = sh21->debug_tty;
}
