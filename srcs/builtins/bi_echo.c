/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:44:45 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/16 15:18:55 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_printf.h"
#include "libft.h"
#include "builtins.h"


int				write_echo_special_codes(char *argv, int *cursor)
{
	if (*argv == 'a')
		write(STDOUT_FILENO, "\a", 1);
	else if (*argv == 'b')
		write(STDOUT_FILENO, "\b", 1);
	else if (*argv == 'c')
		return (0);
	else if (*argv == 'f')
		write(STDOUT_FILENO, "\f", 1);
	else if (*argv == 'n')
		write(STDOUT_FILENO, "\n", 1);
	else if (*argv == 'r')
		write(STDOUT_FILENO, "\r", 1);
	else if (*argv == 't')
		write(STDOUT_FILENO, "\t", 1);
	else if (*argv == 'v')
		write(STDOUT_FILENO, "\v", 1);
	else if (*argv == '\\')
		write(STDOUT_FILENO, "\\", 1);
	else if (*argv == '0')
		ft_printf("%c", ft_atoi_base(argv, "01234567"));
	else if (*argv == '\0' || *argv == ' ')
		write(STDOUT_FILENO, "\\", 1);
	else
		return (2);
	(*cursor) += 1;
	while (ft_isdigit((*argv)++))
		(*cursor)++;
	return (1);
}

int				bi_echo(int argc, char **argv, char ***environ)
{
	int i;
	int ii;
	int should_print_nl;
	int stock;

	(void)environ;
	(void)argc;
	if (!argv[1])
		return (0 * ft_printf("\n"));
	should_print_nl = (!ft_strcmp(argv[1], "-n") ? 0 : 1);
	i = !should_print_nl;
	while (argv[++i] && (ii = -1))
	{
		if (i != 1 && should_print_nl)
			write(STDOUT_FILENO, " ", 1);
		while (argv[i][++ii])
			if (argv[i][ii] == '\\')
			{
				if (!(stock = write_echo_special_codes(&(argv[i][ii + 1])
					, &ii)))
					return (0);
				if (stock == 2)
					write(STDOUT_FILENO, &(argv[i][ii]), 1);
			}
			else
				write(STDOUT_FILENO, &(argv[i][ii]), 1);
	}
	if (should_print_nl)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
