/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:23:14 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/20 17:18:10 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H
# include "libft.h"
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
typedef unsigned char t_jc_tag;
typedef enum { NONE, RUNNING, DONE, SUSPENDED } t_jc_status;
// https://www.usna.edu/Users/cs/aviv/classes/ic221/s16/lec/17/lec.html

typedef	struct			s_jc_job
{
	int					pgid;
	t_jc_tag			tag;
	t_list				*pid_list;
	t_jc_status			status;
}						t_jc_job;

typedef	struct			s_jc
{
	t_list				*job_list;
	t_jc_job			*fg_jobs;
}						t_jc;


t_jc			*jc_get(void);
t_jc_tag		jc_create_tag(void);
void			jc_add(t_jc_tag jtag, pid_t npid);

#endif
