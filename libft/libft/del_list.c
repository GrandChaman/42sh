/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:59:26 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/14 17:19:23 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del_list(void **elem, void (*f)(void**))
{
	t_void *ptr;

	ptr = *elem;
	while (ptr)
	{
		ptr = ptr->next;
		f(elem);
		*elem = ptr;
	}
}
