/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_create_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:04:55 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/22 13:10:58 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_btree		*ft_btree_create_node(void *item)
{
	t_btree *new;

	new = malloc(sizeof(t_btree));
	if (!new)
		ft_perror("malloc", "Mallocation failed. Aborting");
	new->item = item;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	return (new);
}
