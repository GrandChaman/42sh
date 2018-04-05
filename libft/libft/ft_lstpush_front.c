/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:09:37 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/05 17:51:59 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstpush_front(t_list **begin_list, void *data, size_t size)
{
	t_list *tmp;

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
	tmp->next = *begin_list;
	(*begin_list)->prev = tmp;
	tmp->prev = NULL;
	*begin_list = tmp;
}
