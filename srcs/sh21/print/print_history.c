/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:31:18 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/21 11:33:41 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	print_history(t_dlinked *history_list, int fd)
{
	int			i;
	t_dlinked	*tmp;

	i = 0;
	tmp = history_list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		ft_fprintf(fd, "command %d : %s\n", i, tmp->command);
		i++;
		tmp = tmp->previous;
	}
}
