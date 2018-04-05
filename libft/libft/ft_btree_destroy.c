/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 14:25:30 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/03 18:42:48 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		ft_btree_destroy(t_btree **root)
{
	if (!root || !(*root))
		return ;
	if ((*root)->left)
		ft_btree_destroy(&((*root)->left));
	if ((*root)->right)
		ft_btree_destroy(&((*root)->right));
	free((*root)->item);
	free(*root);
	*root = NULL;
}
