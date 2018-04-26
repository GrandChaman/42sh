/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:32:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/26 15:32:53 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void		jc_set_job_as_running(t_jc_job *job)
{
	t_list		*proc_list;
	t_jc_proc	*proc;

	proc_list = job->proc_list;
	while (proc_list)
	{
		proc = (t_jc_proc*)proc_list->content;
		proc_list = proc_list->next;
		proc->status = RUNNING;
	}
}
