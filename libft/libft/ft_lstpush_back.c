/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:09:32 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/21 20:25:55 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstpush_back(t_list **begin_list, void *data, size_t size)
{
	t_list	*tmp;
	t_list	*cursor;

	if (begin_list == NULL)
		return ;
	if (!(tmp = ft_lstnew(data, size)))
		return ;
	if (*begin_list == NULL)
	{
		*begin_list = tmp;
		tmp->next = NULL;
		return ;
	}
	cursor = *begin_list;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = tmp;
	tmp->prev = cursor;
}
