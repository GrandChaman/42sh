/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:08:48 by bluff             #+#    #+#             */
/*   Updated: 2018/01/21 20:25:41 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*el;

	if (!(el = (t_list*)malloc(sizeof(t_list))))
		ft_perror("malloc", "Mallocation failed. Aborting");
	if (content)
	{
		if (!(el->content = malloc(content_size)))
			ft_perror("malloc", "Mallocation failed. Aborting");
		ft_memcpy(el->content, content, content_size);
		el->content_size = content_size;
	}
	else
	{
		el->content = NULL;
		el->content_size = 0;
	}
	el->next = NULL;
	el->prev = NULL;
	return (el);
}
