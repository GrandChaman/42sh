/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 13:13:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/21 15:29:50 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <signal.h>

int		jc_set(t_jc_tag tag, int mode)
{
	t_list		*jb_list;
	t_jc_job*	tmp;

	jb_list = jc_get()->job_list;
	while (jb_list)
	{
		tmp = ((t_jc_job*)jb_list->content);
		if (tmp->tag == tag)
		{
			if (mode == BG)
			{
				ft_printf("[%d] %d (%C)\n", tmp->tag, tmp->pgid, 8675);
				return (tcsetpgrp(STDIN_FILENO, getpgrp()));
			}
			ft_printf("[%d] %d (%C)\n", tmp->tag, tmp->pgid, 8673);
			killpg(tmp->pgid, SIGCONT);
			jc_get()->fg_job = jb_list;
			return (tcsetpgrp(STDIN_FILENO, tmp->pgid));
		}
		jb_list = jb_list->next;
	}
	return (0);
}
