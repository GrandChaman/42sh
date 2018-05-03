/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_create_tag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:20:27 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/26 22:03:36 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static int		sort_jc_tag(void *el1, void *el2)
{
	t_jc_job	*job1;
	t_jc_job	*job2;

	job1 = (t_jc_job*)el1;
	job2 = (t_jc_job*)el2;
	return (job1->tag - job2->tag);
}

t_jc_tag		jc_create_tag(void)
{
	t_jc_job	*jc_job;
	t_list		*tmp;
	t_jc_tag	res;

	jc_job = ft_memalloc(sizeof(t_jc_job));
	jc_job->tag = 0;
	tmp = jc_get()->job_list;
	while (tmp)
	{
		if (jc_job->tag == ((t_jc_job*)tmp->content)->tag)
			jc_job->tag++;
		else
			break ;
		tmp = tmp->next;
	}
	ft_lstpush_back(&jc_get()->job_list, jc_job, sizeof(t_jc_job));
	ft_lstsort(&jc_get()->job_list, sort_jc_tag);
	res = jc_job->tag;
	free(jc_job);
	return (res);
}
