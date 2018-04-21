/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_by_pid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 15:35:53 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/21 15:40:12 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_jc_job	*jc_get_by_pid(pid_t pid)
{
	t_list		*jb_list;
	t_list		*pid_list;
	t_jc_job*	tmp;

	jb_list = jc_get()->job_list;
	while (jb_list)
	{
		tmp = ((t_jc_job*)jb_list->content);
		pid_list = tmp->pid_list;
		while (pid_list)
			if (*((pid_t*)pid_list->content) == pid)
				return (tmp);
			else
				pid_list = pid_list->next;
		jb_list = jb_list->next;
	}
}
