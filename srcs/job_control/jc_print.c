/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:52:14 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/24 12:54:17 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void	jc_print(t_jc_job *job)
{
	t_list		*pid_list;
	size_t		numlen;

	pid_list = job->pid_list;
	if (!pid_list)
		return ;
	numlen = ft_numlen(job->tag);
	ft_printf("[%d]  + %d %s\n", job->tag, *((int*)pid_list->content),
		g_jc_status_string[job->status]);
	while ((pid_list = pid_list->next))
		ft_printf("%*d %s\n", 7 + numlen + ft_numlen(*((int*)
			pid_list->content)), *((int*)pid_list->content),
			g_jc_status_string[job->status]);
}
