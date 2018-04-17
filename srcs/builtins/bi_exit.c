/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:38:41 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/17 14:31:10 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"

int		bi_exit(int argc, char **argv, char ***environ)
{
	(void)argc;
	(void)argv;
	(void)environ;
	del_sh21_exit();
	ft_exit(0, NULL);
	return (0);
}

void	ft_exit(int err, const char *s)
{
	t_sh21 *sh21;

	sh21 = sh21_get();
	if (err)
		ft_error(err, s);
	exit(err);
}
