/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:58:28 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/22 13:25:49 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void		jc_add(t_jc_tag jtag, pid_t npid)
{
	t_list		*jb_list;
	t_jc_job*	tmp;

	jb_list = jc_get()->job_list;
	while (jb_list)
	{
		tmp = ((t_jc_job*)jb_list->content);
		if (tmp->tag == jtag)
		{
			if (!tmp->pid_list)
			{
				if (setpgid(npid, npid) < 0)
					ft_perror("setpgid", "called to setpgid failed.");
				tmp->pgid = npid;
			}
			ft_lstpush_back(&tmp->pid_list, &npid, sizeof(pid_t));
			return ;
		}
		jb_list = jb_list->next;
	}
}
