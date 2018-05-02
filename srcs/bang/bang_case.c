/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:13:53 by fbertoia          #+#    #+#             */
/*   Updated: 2018/05/02 13:27:07 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		bang_error(void)
{
	ft_error(-9, "!");
	return (0);
}

int		case_bang(char **str, int *i)
{
	int		j;
	char	*bang;

	j = 1;
	bang = NULL;
	if (!(*str)[*i + j])
		return (bang_error());
	else if ((*str)[*i + j] == ' ')
		return (*i += j);
	else if ((*str)[*i + j] == '!')
	{
		if (get_ft_shell()->history && get_ft_shell()->history->content)
			bang = ft_strdup(((t_ft_hist_entry*)(get_ft_shell()->history->content))->command);
		(!bang ? bang_error() : (0));
	}
	else if (ft_isdigit((*str)[*i + j]) || (*str)[*i + j] == '-')
		bang = get_history_at(ft_atoi((*str) + *i + j), &j);
	else
		bang = cmp_history(*str + *i + j, &j);
	if (!bang)
		return (0);
	replace_bang(str, i, &j, bang);
	*i += ft_strlen(bang);
	ft_strdel(&bang);
	return (1);
}

int		case_backslash_bang(char *str, int *i, char c)
{
	int ret;

	*i += 1;
	ret = str[*i] == c;
	if (str[*i])
		*i += 1;
	return (ret);
}

void	case_quote_bang(char *str, int *i)
{
	*i += 1;
	while (str[*i] && (str[*i] != '\'' || case_backslash_bang(str, i, str[*i])))
		*i += 1;
}

int		case_dquote_bang(char **str, int *i)
{
	int ret;

	ret = 1;
	*i += 1;
	while ((*str)[*i] && ((*str)[*i] != '"'))
	{
		if ((*str)[*i] == '!')
			ret = case_bang(str, i);
		*i += 1;
	}
	return (ret);
}
