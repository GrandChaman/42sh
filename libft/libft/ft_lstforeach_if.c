/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstforeach_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:09:14 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/07 17:09:15 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstforeach_if(t_list *begin_list,
	void (*f)(void *), void *data_ref, int (*cmp)())
{
	if (begin_list == NULL)
		return ;
	while (begin_list)
	{
		if (!(*cmp)(begin_list->content, data_ref))
			(*f)(begin_list->content);
		begin_list = begin_list->next;
	}
}
