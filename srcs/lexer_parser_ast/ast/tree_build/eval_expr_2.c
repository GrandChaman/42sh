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

// char	*add_str(char **ret, char **ptr, int *i)
// {
// 	*ret = ft_strffjoin(*ret, ft_strndup(*ptr, *i + 1));
// 	*ptr += *i;
// 	*i = 0;
// 	return (*ret);
// }
void	case_dollar_expr(char **ret, char **ptr, int *i)
{
	int		end;
	char 	*tmp;

	end = 0;
	*ret = add_str(ret, ptr, i);
	(*ptr)++;
	tmp = find_var(*ptr);
	*ret = ft_strfjoin(*ret, tmp ? tmp : "0");
	*ptr += skip_var(*ptr);
	free(tmp);
}

char	*find_var_expr(char *str)
{
	int		i;
	char	*ret;
	char	*ptr;

	i = 0;
	ptr = str;
	ret = NULL;
	while (ptr[i])
	{
		if (ptr[i] == '$')
			case_dollar(&ret, &ptr, &i);
		else
			i++;
	}
	if (i)
		ret = add_str(&ret, &ptr, &i);
	ft_printf("***ptr = %s\n", ret);
	free(str);
	return (ret);
}
