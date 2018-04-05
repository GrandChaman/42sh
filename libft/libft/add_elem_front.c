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

void	*add_elem_front(void **alst, void *elem_to_add)
{
	t_void *ptr;

	ptr = (t_void*)elem_to_add;
	if (!alst)
		return (NULL);
	if (!elem_to_add)
		return (*alst);
	if (!*alst)
		return (*alst = elem_to_add);
	ptr->next = *alst;
	*alst = ptr;
	return (*alst);
}
