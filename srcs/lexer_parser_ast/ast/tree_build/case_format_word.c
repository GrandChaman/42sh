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

/*
** The function case_backslash fill an array to keep the index of backslashed
** character that will be interpreted a second time in the split_args function
*/


void	case_backslash(char **ret, char **ptr, int *i, char *special_chars, t_ast_node *node)
{
	int		len;
	int		backslashed;

	backslashed = 0;
	*ret = add_str(ret, ptr, i);
	(*i)++;
	if (!special_chars || ft_strindex(special_chars, (*ptr)[*i]) >= 0)
		(*ptr)++;
	if (**ptr == '\'' || **ptr == '\"' || is_whitespace(**ptr))
		backslashed = 1;
	*ret = add_str(ret, ptr, i);
	if (backslashed)
	{
		len = ft_strlen(*ret);
		node->esc_i[node->nb_escaped_quote] = len ? len - 1 : len;
		if (node->nb_escaped_quote < NB_ESCAPED_QUOTE)
			node->nb_escaped_quote++;
	}
}


// echo $((2 + 3))
// echo 5

void	case_dollar(char **ret, char **ptr, int *i)
{
	int end;

	end = 0;
	*ret = add_str(ret, ptr, i);
	(*ptr)++;
	if (ft_strnequ(*ptr, "((", 2))
	{
		*ret = ft_strjoin(*ret, " ");
		*ret = ft_strjoin(*ret, ft_itoa(ft_eval_expr(*ptr, &end)));
		*ptr += end;
		ft_printf("YA forcement des leaks ou mallocfree , j attend le lexer  me laisse passer");
	}
	else
	{
		*ret = ft_strffjoin(*ret, find_var(*ptr));
		*ptr += skip_var(*ptr);
	}
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

void	case_dquote(char **ret, char **ptr, int *i, t_ast_node *node)
{
	(*i)++;
	while ((*ptr)[*i] && (*ptr)[*i] != '\"')
	{
		if ((*ptr)[*i] == '\\')
			case_backslash(ret, ptr, i, "$`\"\\\n", node);
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
