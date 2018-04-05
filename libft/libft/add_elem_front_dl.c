/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:47:07 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/14 11:47:08 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*add_elem_front_dl(void **alst, void *elem_to_add)
{
	t_void *ptr;
	t_void *ptr_elem_to_add;

	ptr_elem_to_add = (t_void*)elem_to_add;
	ptr = (t_void*)*alst;
	if (!alst)
		return (NULL);
	if (!*alst)
		return (*alst = elem_to_add);
	ptr_elem_to_add->next = *alst;
	ptr->previous = elem_to_add;
	*alst = elem_to_add;
	return (*alst);
}
