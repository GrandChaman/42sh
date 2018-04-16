/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:24:35 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/16 15:02:04 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static char	*norme_0(int i, char *ret, char *ptr, char **str)
{
	if (i)
		ret = add_str(&ret, &ptr, &i);
	ft_strdel(str);
	return (ret);
}

char		*format_word(char **str)
{
	char	*ret;
	char	*ptr;
	int		i;

	i = 0;
	ptr = *str;
	ret = NULL;
	sh21_get()->tree.nb_escaped_quote = 0;
	ft_printf("*str = |%s|\n", *str);
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
			++i;
	}
	return (norme_0(i, ret, ptr, str));
}
