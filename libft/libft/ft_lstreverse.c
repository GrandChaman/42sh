/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:09:45 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/07 17:09:46 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstreverse(t_list **begin_list)
{
	t_list	*curr;
	t_list	*rev;
	t_list	*first;
	int		i;
	int		ii;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	i = 0;
	curr = *begin_list;
	while (curr->next && ++i)
		curr = curr->next;
	first = curr;
	ii = i;
	while (ii--)
	{
		rev = *begin_list;
		while (rev->next != curr)
			rev = rev->next;
		curr->next = rev;
		curr = rev;
	}
	curr->next = 0;
	*begin_list = first;
}
