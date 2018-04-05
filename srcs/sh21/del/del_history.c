/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:50:54 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 14:50:55 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		del_history(void **list)
{
	t_dlinked **tmp;

	if (!list || !*list)
		return ;
	tmp = (t_dlinked **)list;
	ft_strdel(&(*tmp)->command);
	ft_memdel(list);
}
