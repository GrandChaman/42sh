/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:52:14 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/24 14:18:03 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void	jc_print(t_jc_job *job)
{
	t_list		*pid_list;
	size_t		numlen;
	t_jc_proc	*proc;

	pid_list = job->pid_list;
	if (!pid_list)
		return ;
	numlen = ft_numlen(job->tag);
	proc = (t_jc_proc*)pid_list->content;
	ft_printf("[%d]  + %d %s\n", job->tag, proc->pid,
		g_jc_status_string[proc->status]);
	while ((pid_list = pid_list->next))
	{
		proc = (t_jc_proc*)pid_list->content;
		ft_printf("%*d %s\n", 7 + numlen + ft_numlen(proc->pid), proc->pid,
			g_jc_status_string[proc->status]);
	}
}
