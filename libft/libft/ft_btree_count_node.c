/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_count_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:11:06 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/03 18:38:03 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_btree_count_node(t_btree *root)
{
	int i;

	i = 0;
	if (!root)
		return (0);
	if (root->left)
		i += ft_btree_count_node(root->left);
	i++;
	if (root->right)
		i += ft_btree_count_node(root->right);
	return (i);
}
