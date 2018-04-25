/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_expr_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 21:40:56 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/24 21:40:59 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*find_var_expr(char *str)
{
	int		i;
	char	*stock;
	char	*final;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			stock = ft_strffjoin(ft_strsub(str, 0, i), find_var(&str[i + 1]));
			i++;
			while (str[i] && ft_isalpha(str[i]))
				i++;
			final = ft_strjoin(stock, &str[i]);
			free(stock);
			free(str);
			str = final;
		}
		else
			i++;
	}
	return (str);
}
