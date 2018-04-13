/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:24:35 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/15 17:44:27 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char		*format_word(char **str)
{
	char	*ret;
	char	*ptr;
	int		i;

	i = 0;
	ptr = *str;
	ret = NULL;
	while (ptr[i])
	{
		if (ptr[i] == '\\')
			case_backslash(&ret, &ptr, &i, NULL);
		else if (ptr[i] == '~')
			case_tilde(&ret, &ptr, &i);
		else if (ptr[i] == '\'')
			case_quote(&ret, &ptr, &i);
		else if (ptr[i] == '\"')
			case_dquote(&ret, &ptr, &i);
		else if (ptr[i] == '$')
			case_dollar(&ret, &ptr, &i);
		else
			i++;
	}
	if (i)
		ret = add_str(&ret, &ptr, &i);
	ft_strdel(str);
	return (ret);
}
