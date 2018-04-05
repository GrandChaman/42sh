/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstforeach.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:09:18 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/07 17:09:19 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstforeach(t_list *begin_list, void (*f)(void *))
{
	if (begin_list == NULL)
		return ;
	while (begin_list)
	{
		f(begin_list->content);
		begin_list = begin_list->next;
	}
}
