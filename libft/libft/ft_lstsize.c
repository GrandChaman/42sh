/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:09:50 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/07 17:09:51 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_lstsize(t_list *begin_list)
{
	int c;

	if (begin_list == NULL)
		return (0);
	c = 1;
	while ((begin_list = begin_list->next))
		c++;
	return (c);
}
