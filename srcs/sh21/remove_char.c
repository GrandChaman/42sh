/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 12:40:21 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/18 12:40:23 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void 	case_quote_rm(char *str, int *i)
{
	char c;

	c = str[*i];
	*i += 1;
	while (str[*i] && str[*i] != c)
		*i += 1;
}

void 	case_backslash_rm(char *str, int *i)
{
	if (str[*i + 1] == '\n')
		str = ft_strcpy(str + *i, str + *i + 2);
	else
		*i += 1;
}

char	*remove_char(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			case_quote_rm(str, &i);
		else if (str[i] == '\\')
			case_backslash_rm(str, &i);
		else
			i++;
	}
	return (str);
}
