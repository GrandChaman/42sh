/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/16 15:19:03 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int escaped_char(char *argv, t_ast *tree, int *i, int *j)
{
	if (argv[*i + *j] == '\'' || argv[*i + *j] == '\"'
	|| is_whitespace(argv[*i + *j]))
	{
		if (tree->i < tree->nb_escaped_quote && tree->esc_i[tree->i]
			== (*i + *j + tree->quote_count))
		{
			tree->i++;
			return (1);
		}
	}
	return (0);
}

void case_quote_args(char *argv, int *i, int *j)
{
	t_ast	*tree;
	char	c;

	tree = &sh21_get()->tree;
	c = argv[*i + *j];
	if (escaped_char(argv, tree, i, j))
		return ;
	else
	{
		ft_strcpy(argv + *i + *j, argv + *i + *j + 1);
		tree->quote_count += 1;
		while (argv[*i + *j] && (argv[*i + *j] != c
		|| escaped_char(argv, tree, i, j)))
			*j += 1;
		ft_strcpy(argv + *i + *j, argv + *i + *j + 1);
		tree->quote_count += 1;
	}
}


t_args *new_args(char *argv, int *j, int *i)
{
	t_args *new_el;

	if (!(new_el = (t_args*)malloc(sizeof(t_args))))
		del_sh21_exit();
	new_el->content = ft_strndup(argv + *i, *j + 1);
	new_el->next = NULL;
	*i += *j;
	*j = 0;
	return (new_el);
}

void case_space(char *argv, int *i, int *j, t_args **list)
{
	if (escaped_char(argv, &sh21_get()->tree, i, j))
		*j += 1;
	else if (*j)
		add_elem_back((void**)list, (void*)new_args(argv, j, i));
	else
		*i += 1;
}
