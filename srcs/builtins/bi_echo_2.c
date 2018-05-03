/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:29:05 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/28 17:29:07 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_retour(int should_print_nl)
{
	if (should_print_nl)
		write(STDOUT_FILENO, "\n", 1);
}

int		print_backslash(char **argv, int i, int ii)
{
	if (!argv[i][ii + 1])
	{
		write(STDOUT_FILENO, "\\", 1);
		return (1);
	}
	return (0);
}

void	print_space(char **argv, int should_print_nl, int i)
{
	if ((flag_echo(argv, &should_print_nl)) != i)
		write(STDOUT_FILENO, " ", 1);
}
