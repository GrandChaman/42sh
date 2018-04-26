/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 12:40:21 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/23 18:15:31 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	case_quote_rm(char *str, int *i)
{
	char c;

	c = str[*i];
	*i += 1;
	while (str[*i] && str[*i] != c)
		*i += 1;
}

static void	case_backslash_rm(char *str, int *i)
{
	while (str[*i + 1] == ' ' || str[*i + 1] == '\t')
		*i += 1;
	if (str[*i + 1] == '\n')
		str = ft_strcpy(str + *i, str + *i + 2);
	else
		*i += 1;
}

static void	case_remove_chariot(char *str, int *i)
{
	while (str[*i + 1] == ' ' || str[*i + 1] == '\t')
		*i += 1;
	if (str[*i + 1] == '\n')
		str = ft_strcpy(str + *i + 1, str + *i + 2);
	else
		*i += 1;
}

char		*remove_char(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			case_quote_rm(str, &i);
		else if (str[i] == '\\')
			case_backslash_rm(str, &i);
		else if (str[i] == '&' && i != 0 && str[i - 1] == '&')
			case_remove_chariot(str, &i);
		else if (str[i] == '|' && i != 0 && str[i - 1] == '|')
			case_remove_chariot(str, &i);
		else if (str[i] == '|')
			case_remove_chariot(str, &i);
		else
			i++;
	}
	return (str);
}
