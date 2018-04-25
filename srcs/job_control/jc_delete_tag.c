/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_delete_tag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:35:08 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/25 09:37:26 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static void	delete_jc_proc(void *el, size_t size)
{
	(void)size;
	free(((t_jc_proc*)el)->cmd);
	free(el);
}

static void	delete_jc_tag(void *el, size_t size)
{
	(void)size;
	ft_lstdel(&(((t_jc_job*)el)->proc_list), delete_jc_proc);
	free(el);
}

void		jc_delete_tag(t_jc_tag tag)
{
	t_jc		*jc;
	t_list		*jb_list;
	t_jc_job	*tmp;

	jc = jc_get();
	jb_list = jc->job_list;
	while (jb_list)
	{
		tmp = ((t_jc_job*)jb_list->content);
		if (tmp->tag == tag)
		{
			if (jc->fg_job == tmp)
				jc->fg_job = NULL;
			ft_lstdelone((jb_list == jc->job_list ? &jc->job_list : &jb_list),
				delete_jc_tag);
			return ;
		}
		jb_list = jb_list->next;
	}
}
