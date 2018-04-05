/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:10:41 by bluff             #+#    #+#             */
/*   Updated: 2018/01/23 11:22:24 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_free_without_size(void *el, size_t ignored)
{
	(void)ignored;
	free(el);
}

void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (!del)
		del = &ft_free_without_size;
	tmp = *alst;
	if (tmp->content)
		del(tmp->content, tmp->content_size);
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	*alst = tmp->next;
	free(tmp);
}
