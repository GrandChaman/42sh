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

static int operator(char *c, int i)
{
	if (c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/' || c[i] == '%')
		return (1);
	return (0);
}

static int is_whitespace_1(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		*i = *i + 1;
	if (str[*i] == '\0')
		return (0);
	return (1);
}

int	correct_form_eval_expr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(is_whitespace_1(str, &i)))
			break ;
		if ((!(ft_isalnum(str[i]))) && str[i] != '(')
			return (0);
		else
		{
			while (ft_isalnum(str[i]) || str[i] == '(')
				i++;
		}
		if (!(is_whitespace_1(str, &i)))
			break ;
		while (str[i] == ')')
			i++;
		if (!(is_whitespace_1(str, &i)))
			break ;
		if (!(operator(str, i)))
			return (0);
		i++;
		if (!(is_whitespace_1(str, &i)))
			return (0);
	}
	return (1);
}