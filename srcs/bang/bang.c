/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:13:14 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/26 15:13:15 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int	bang(char **str)
{
	int i;
	int ret;

	ret = 1;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\')
			case_backslash_bang(*str, &i, (*str)[i]);
		else if ((*str)[i] == '\'')
			case_quote_bang(*str, &i);
		else if ((*str)[i] == '\"')
			ret = case_dquote_bang(str, &i);
		else if ((*str)[i] == '!')
			ret = case_bang(str, &i);
		else
			i++;
		if (!ret)
		{
			ft_strdel(str);
			break ;
		}
	}
	return (ret);
}
