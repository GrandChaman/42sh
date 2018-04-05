/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 19:43:13 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/04 17:30:08 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_btree	*ft_btree_create_node_and_set_parent(void *item,
	t_btree *parent)
{
	t_btree *res;

	res = ft_btree_create_node(item);
	res->parent = parent;
	return (res);
}

void			ft_btree_insert_data(t_btree **root, void *item,
	int (*cmpf)(void *, void *))
{
	if (!root)
		return ;
	if (!(*root))
	{
		*root = ft_btree_create_node(item);
		return ;
	}
	if (cmpf((*root)->item, item) <= 0)
	{
		if ((*root)->right)
			ft_btree_insert_data(&((*root)->right), item, cmpf);
		else
			(*root)->right = ft_btree_create_node_and_set_parent(item, *root);
	}
	else
	{
		if ((*root)->left)
			ft_btree_insert_data(&((*root)->left), item, cmpf);
		else
			(*root)->left = ft_btree_create_node_and_set_parent(item, *root);
	}
}
