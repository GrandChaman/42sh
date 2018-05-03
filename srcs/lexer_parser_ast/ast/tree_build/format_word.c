/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:24:35 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/17 16:05:33 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "builtins.h"

static char	*norme_0(int i, char *ret, char *ptr, char **str)
{
	if (i)
		ret = add_str(&ret, &ptr, &i);
	ft_strdel(str);
	return (ret);
}

static void	initialize_values(t_ast_node *node, char **ptr,
			char **str, char **ret)
{
	*ptr = *str;
	node->nb_escaped_quote = 0;
	node->i = 0;
	node->quote_count = 0;
	ft_memset(node->esc_i, -1, NB_ESCAPED_QUOTE);
	*ret = NULL;
}

char		*format_word(char **str, t_ast_node *node)
{
	char	*ret;
	char	*ptr;
	int		i;

	i = 0;
	if (!*str)
		return (NULL);
	initialize_values(node, &ptr, str, &ret);
	while (ptr[i])
	{
		if (ptr[i] == '\\' && !(node->special_chars = NULL))
			case_backslash(&ret, &ptr, &i, node);
		else if (ptr[i] == '~')
			case_tilde(&ret, &ptr, &i);
		else if (ptr[i] == '\'')
			case_quote(&ret, &ptr, &i);
		else if (ptr[i] == '\"')
			case_dquote(&ret, &ptr, &i, node);
		else if (ptr[i] == '$')
			case_dollar(&ret, &ptr, &i);
		else
			++i;
	}
	return (norme_0(i, ret, ptr, str));
}
