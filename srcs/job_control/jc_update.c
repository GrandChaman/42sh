/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 13:33:03 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/22 15:06:52 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static void	jc_update_routine(t_jc_job *job, int status)
{
	t_jc	*jc;

	jc = jc_get();
	if (WIFEXITED(status) || WIFSIGNALED(status))
	{
		job->status = (WIFEXITED(status) ? DONE : KILLED);
		if (job != jc->fg_job || job->status == KILLED)
			jc_print(job);
		if (job == jc->fg_job)
			jc->fg_job = NULL;
		jc_delete_tag(job->tag);
		return ;
	}
	else if (WIFSTOPPED(status))
		job->status = SUSPENDED;
	else
		job->status = RUNNING;
	if (job != jc->fg_job)
		jc_print(job);
}

void		jc_update(t_jc_tag tag, int status)
{
	t_list		*jb_list;
	t_jc_job*	job;

	jb_list = jc_get()->job_list;
	while (jb_list)
	{
		job = ((t_jc_job*)jb_list->content);
		if (job->tag == tag)
		{
			jc_update_routine(job, status);
			return ;
		}
		jb_list = jb_list->next;
	}
}
