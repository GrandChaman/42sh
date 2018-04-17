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
	t_ast	*tree;
	int		len;
	int		quote;

	quote = 0;
	tree = &sh21_get()->tree;
	*ret = add_str(ret, ptr, i);
	(*i)++;
	if (!special_chars || ft_strindex(special_chars, (*ptr)[*i]) >= 0)
		(*ptr)++;
	if (**ptr == '\'' || **ptr == '\"')
		quote = 1;
	*ret = add_str(ret, ptr, i);
	if (quote)
	{
		len = ft_strlen(*ret);
		tree->esc_i[tree->nb_escaped_quote] = len ? len - 1 : len;
		if (tree->nb_escaped_quote < NB_ESCAPED_QUOTE)
			tree->nb_escaped_quote++;
	}
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
