/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/23 18:04:42 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	del_el(void **el)
{
	t_args **ptr;

	ptr = (t_args**)el;
	ft_strdel(&(*ptr)->content);
	ft_memdel((void**)ptr);
}

char	**copy_list_to_array(t_args **list)
{
	int		len;
	char	**ret;
	t_args	*ptr;
	int		i;

	ptr = *list;
	i = 0;
	len = size_list((void**)list);
	ret = (char**)malloc(sizeof(char*) * (len + 1));
	if (!ret)
		del_sh21_exit();
	while (ptr)
	{
		ret[i++] = ft_strdup(ptr->content);
		ptr = ptr->next;
	}
	ret[i] = NULL;
	del_list((void**)list, del_el);
	return (ret);
}

char	**split_args(char *argv, t_ast_node *node)
{
	t_args		*list;
	int			i;
	int			j;
	int			*tabi[2];

	tabi[0] = &i;
	tabi[1] = &j;
	list = NULL;
	i = 0;
	j = 0;
	while (argv[i + j])
	{
		if (escaped_char(argv, node, &i, &j))
			j++;
		else if (argv[i + j] == '\"' || argv[i + j] == '\'')
			case_quote_args(argv, &i, &j, node);
		else if (is_whitespace(argv[i + j]))
			case_space(argv, tabi, node, &list);
		else
			j++;
	}
	if (j)
		add_elem_back((void**)&list, new_args(argv, &j, &i));
	return (copy_list_to_array(&list));
}
