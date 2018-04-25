/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/23 18:02:54 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		escaped_char(char *argv, t_ast_node *node, int *i, int *j)
{
	if (argv[*i + *j] == '\'' || argv[*i + *j] == '\"'
		|| is_whitespace(argv[*i + *j]))
	{
		if (node->i < node->nb_escaped_quote && node->esc_i[node->i]
			== (*i + *j + node->quote_count))
		{
			node->i++;
			return (1);
		}
	}
	return (0);
}

void	case_quote_args(char *argv, int *i, int *j, t_ast_node *node)
{
	char	c;

	c = argv[*i + *j];
	if (escaped_char(argv, node, i, j))
		return ;
	else
	{
		ft_strcpy(argv + *i + *j, argv + *i + *j + 1);
		node->quote_count += 1;
		while (argv[*i + *j] && (argv[*i + *j] != c
		|| escaped_char(argv, node, i, j)))
			*j += 1;
		ft_strcpy(argv + *i + *j, argv + *i + *j + 1);
		node->quote_count += 1;
	}
}

t_args	*new_args(char *argv, int *j, int *i)
{
	t_args	*new_el;

	if (!(new_el = (t_args*)malloc(sizeof(t_args))))
		del_sh21_exit();
	new_el->content = ft_strndup(argv + *i, *j + 1);
	new_el->next = NULL;
	*i += *j;
	*j = 0;
	return (new_el);
}

void	case_space(char *argv, int *i[2], t_ast_node *node, t_args **list)
{
	if (escaped_char(argv, node, i[0], i[1]))
		*(i[1]) += 1;
	else if (*(i[1]))
		add_elem_back((void**)list, (void*)new_args(argv, i[1], i[0]));
	else
		*(i[0]) += 1;
}
