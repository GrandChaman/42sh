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