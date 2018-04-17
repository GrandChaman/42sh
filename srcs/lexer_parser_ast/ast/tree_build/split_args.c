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
// static int		get_next_quote(char *argv, char quote)
// {
// 	int		i;
//
// 	i = 1;
// 	while (argv[i] && argv[i] != quote)
// 		i++;
// 	if (argv[i])
// 		i++;
// 	return (i);
// }
//
// static void		case_whitespace(char **argv, int *wd_nb, int *flag)
// {
// 	while (is_whitespace(**argv))
// 		(*argv)++;
// 	if (*flag)
// 		(*wd_nb)++;
// 	*flag = 0;
// }
//
// static int		word_number(char *argv)
// {
// 	int		wd_nb;
// 	int		flag;
// 	int 	array_quote;
//
// 	flag = 0;
// 	wd_nb = 0;
// 	array_quote = 0;
// 	while (*argv)
// 	{
// 		if (*argv == (char)'\'' || *argv == (char)'\"')
// 		{
// 			argv += get_next_quote(argv, *argv);
// 			flag = 1;
// 		}
// 		else if (is_whitespace(*argv))
// 			case_whitespace(&argv, &wd_nb, &flag);
// 		else
// 		{
// 			while (!is_whitespace(*argv) && ft_isprint(*argv) && *argv
// 			!= (char)'\'' && *argv != (char)'\"')
// 				argv++;
// 			flag = 1;
// 		}
// 	}
// 	return (wd_nb + flag);
// }
//
char			*word(char **argv)
{
	char	*ret;
	int		i;
	char	quote;
	int		flag;

	ret = NULL;
	i = 0;
	flag = 0;
	while ((*argv)[i] && ft_isprint((*argv)[i]) && !is_whitespace((*argv)[i]))
	{
		if ((*argv)[i] == (char)'\'' || (*argv)[i] == (char)'\"')
		{
			quote = (*argv)[i];
			ft_memmove(*argv + i, *argv + i + 1, ft_strlen(*argv + i + 1));
			while ((*argv)[i] && (*argv)[i] != quote)
				++i;
			ft_memmove(*argv + i, *argv + i + 1, ft_strlen(*argv + i));
		}
		else
			i++;
	}
	ret = ft_strndup(*argv, i + 1);
	*argv += i;
	return (ret);
}
//
// char			**split_args(char *argv)
// {
// 	char	**ret;
// 	int		wd_nb;
// 	int		i;
// 	char	**u;
//
// 	i = 0;
// 	wd_nb = word_number(argv);
// 	if (!(ret = (char**)malloc(sizeof(char*) * (wd_nb + 1))))
// 	{
// 		ft_error(errno, "malloc");
// 		return (NULL);
// 	}
// 	while (*argv && i < wd_nb)
// 	{
// 		while (*argv && is_whitespace(*argv))
// 			argv++;
// 		ret[i++] = word(&argv);
// 	}
// 	ret[i] = NULL;
// 	u = ret;
// 	while (*u)
// 		++u;
// 	return (ret);
// }

int escaped_quote(char *argv, t_ast *tree, int *i, int *j)
{
	if (argv[*i + *j] == '\'' || argv[*i + *j] == '\"')
	{
		if (tree->i < tree->nb_escaped_quote && tree->esc_i[tree->i] == (*i + *j + tree->quote_count))
		{
			// ft_printf("*************escaped quote********** tree->nb_escaped_quote = %d, tree->esc_i[tree->i] = %d  tree->i = %d, i + j = %d, tree->quote = %d\n",
			// tree->nb_escaped_quote, tree->esc_i[tree->i], tree->i, *i + *j, tree->quote_count);
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
	if (escaped_quote(argv, tree, i, j))
		return ;
	else
	{
		ft_strcpy(argv + *i + *j, argv + *i + *j + 1);
		tree->quote_count += 1;
		while (argv[*i + *j] && (argv[*i + *j] != c || escaped_quote(argv, tree, i, j)))
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
	if (*j)
		add_elem_back((void**)list, (void*)new_args(argv, j, i));
	else
		*i += 1;
}

void del_el(void **el)
{
	t_args **ptr;

	ptr = (t_args**)el;
	ft_strdel(&(*ptr)->content);
	ft_memdel((void**)ptr);
}

char **copy_list_to_array(t_args **list)
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
	// i = 0;
	// while (ret[i] && ft_printf("arg[%d] = |%s|\n", i, ret[i]))
	// 	i++;
	return (ret);
}

char **split_args(char *argv)
{
	t_args	*list;
	int		i;
	int		j;

	list = NULL;
	i = 0;
	j = 0;
	sh21_get()->tree.i = 0;
	sh21_get()->tree.quote_count = 0;
	while (argv[i + j])
	{
		// ft_printf("argv = %s, i = %d, j = %d\n", argv + i + j, i, j);
		if (argv[i + j] == '\"' || argv[i + j] == '\'')
			case_quote_args(argv, &i, &j);
		else if (is_whitespace(argv[i + j]))
			case_space(argv, &i, &j, &list);
		else
			j++;
	}
	if (j)
		add_elem_back((void**)&list, new_args(argv, &j, &i));
	return (copy_list_to_array(&list));
}
