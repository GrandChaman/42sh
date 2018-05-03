/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:41:18 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/25 10:18:16 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			is_operator(char c)
{
	return (c == ',' || c == '_' || c == '+' || c == ':' || c == '@' || c == '%'
	|| c == '/' || c == '-' || c == '.');
}

char				*escape_operator(char *str)
{
	int		i;
	int		len;
	char	*res;

	i = -1;
	len = -1;
	while (str[++i] && (++len >= 0))
	{
		if ((!ft_isalnum(str[i]) && !is_operator(str[i]))
			&& ((i > 0 && str[i - 1] != '\\') || i == 0))
			len++;
	}
	i = 0;
	res = ft_strnew(len + 1);
	len = 0;
	while (str[i])
	{
		if ((!ft_isalnum(str[i]) && !is_operator(str[i]))
			&& ((i > 0 && str[i - 1] != '\\') || i == 0))
			res[len++] = '\\';
		res[len] = str[i];
		i++;
		len++;
	}
	return (res);
}
