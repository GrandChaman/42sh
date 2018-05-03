/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:09:04 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/04 19:40:37 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstat(t_list *begin_list, int nbr)
{
	int i;

	i = 0;
	if (begin_list == NULL && i >= 0)
		return (NULL);
	while (begin_list->prev)
		begin_list = begin_list->prev;
	while (i++ < nbr && begin_list)
		begin_list = begin_list->next;
	return (begin_list);
}
