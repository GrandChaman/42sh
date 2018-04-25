/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:38:41 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/25 13:16:30 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"

int		bi_exit(int argc, char **argv, char ***environ, t_ast_node *root)
{
	(void)argc;
	(void)argv;
	(void)root;
	(void)environ;
	if (jc_get()->job_list)
	{
		ft_fprintf(2, "Jobs are still running. Please close them before"
			" exiting\n");
		return (1);
	}
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
