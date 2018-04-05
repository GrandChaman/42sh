/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdestroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:21:52 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/22 13:26:12 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_free_without_size(void *el, size_t ignored)
{
	(void)ignored;
	free(el);
}

void		ft_lstdestroy(t_list **list)
{
	ft_lstdel(list, &ft_free_without_size);
}
