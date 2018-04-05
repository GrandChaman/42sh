/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_prefix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:44:20 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/03 11:54:47 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	if (!root || !applyf)
		return ;
	applyf(root->item);
	if (root->left)
		ft_btree_apply_prefix(root->left, applyf);
	if (root->right)
		ft_btree_apply_prefix(root->right, applyf);
}
