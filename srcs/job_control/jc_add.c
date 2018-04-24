/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:58:28 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/24 15:42:25 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "job_control.h"

void		jc_add(t_jc_tag jtag, pid_t npid)
{
	t_list		*jb_list;
	t_jc_proc	proc;
	t_jc_job*	tmp;

	ft_printf("{green}%d - call jc_add(%d, %d){eoc}\n", getpid(), jtag, npid);
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
			else if (setpgid(npid, tmp->pgid) < 0)
				ft_perror("setpgid", "called to setpgid failed.");
			proc.pid = npid;
			ft_lstpush_back(&tmp->pid_list, &proc, sizeof(t_jc_proc));
			return ;
		}
		jb_list = jb_list->next;
	}
}
