/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:44:15 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/22 13:53:15 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

void				delete_hist_entry(void *entry, size_t size)
{
	t_ft_hist_entry *hentry;

	(void)size;
	hentry = (t_ft_hist_entry*)entry;
	free(hentry->command);
	free(hentry);
}

void				trim_history(t_ft_sh *sh)
{
	int		i;
	t_list	*lcpy;

	i = 0;
	lcpy = sh->history;
	while (i++ < SH_HIST_MAX_SIZE && lcpy)
		lcpy = lcpy->next;
	if (lcpy)
	{
		ft_lstdel(&lcpy, delete_hist_entry);
		sh->history_size = SH_HIST_MAX_SIZE;
	}
}
