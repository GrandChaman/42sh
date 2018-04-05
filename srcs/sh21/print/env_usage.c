/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 21:15:00 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/14 21:20:22 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		env_usage(char c, int option)
{
	if (option == 2)
		ft_fprintf(2, "env: option requires an argument -- %c\n", c);
	ft_fprintf(2, "usage: env [-i] [-P utilpath] [-u name]\
	[name=value ...] [utility [argument ...]]\n");
	return (1);
}
