/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:30:37 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:30:45 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int	my_putchar(int c)
{
	t_sh21 *sh21;

	sh21 = sh21_get();
	ft_putchar_fd(c, sh21->input.tty);
	return (c);
}
