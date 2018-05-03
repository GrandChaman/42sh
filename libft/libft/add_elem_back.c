/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:47:15 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/05 16:10:28 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*add_elem_back(void **alst, void *elem_to_add)
{
	t_void *ptr;

	if (!alst)
		return (NULL);
	if (!elem_to_add)
		return (*alst);
	ptr = (t_void*)*alst;
	if (!*alst)
		return (*alst = elem_to_add);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = elem_to_add;
	return (ptr->next);
}
