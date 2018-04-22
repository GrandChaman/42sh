/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 13:33:03 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/22 16:06:04 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void		jc_update(t_jc_job *job, int status)
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
