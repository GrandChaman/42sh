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

void	case_backslash(char **ret, char **ptr, int *i, char *special_chars)
{
	int quote;

	*ret = add_str(ret, ptr, i);
	(*i)++;
	if (!special_chars || ft_strindex(special_chars, (*ptr)[*i]) >= 0)
		(*ptr)++;
	ft_printf("voici le charactere courant = |%c|", *ptr);
	*ret = add_str(ret, ptr, i);
}

void	case_dollar(char **ret, char **ptr, int *i)
{
	*ret = add_str(ret, ptr, i);
	(*ptr)++;
	*ret = ft_strffjoin(*ret, find_var(*ptr));
	*ptr += skip_var(*ptr);
}

void	case_quote(char **ret, char **ptr, int *i)
{
	(*i)++;
	while ((*ptr)[*i] && (*ptr)[*i] != '\'')
		(*i)++;
	if ((*ptr)[*i])
		(*i)++;
	*ret = add_str(ret, ptr, i);
}

void	case_dquote(char **ret, char **ptr, int *i)
{
	(*i)++;
	while ((*ptr)[*i] && (*ptr)[*i] != '\"')
	{
		if ((*ptr)[*i] == '\\')
			case_backslash(ret, ptr, i, "$`\"\\\n");
		else if ((*ptr)[*i] == '$')
			case_dollar(ret, ptr, i);
		else
			(*i)++;
	}
	if ((*ptr)[*i])
		(*i)++;
	*ret = add_str(ret, ptr, i);
}

void	case_tilde(char **ret, char **ptr, int *i)
{
	*ret = add_str(ret, ptr, i);
	(*ptr)++;
	*ret = ft_strfjoin(*ret, ft_getenv("HOME", &sh21_get()->env.orig_env));
}
