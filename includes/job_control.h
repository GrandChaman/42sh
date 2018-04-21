/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:23:14 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/21 15:40:21 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H
# include "libft.h"
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# define FG 0
# define BG 1
typedef unsigned char t_jc_tag;
typedef enum { NONE, RUNNING, DONE, SUSPENDED } t_jc_status;
// https://www.usna.edu/Users/cs/aviv/classes/ic221/s16/lec/17/lec.html
//https://stackoverflow.com/questions/10779020/sending-a-process-to-the-background-and-returning-control-to-my-shell

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
	t_jc_job			*fg_job;
}						t_jc;


t_jc			*jc_get(void);
t_jc_tag		jc_create_tag(void);
void			jc_add(t_jc_tag jtag, pid_t npid);
void			jc_delete_tag(t_jc_tag tag);
int				jc_set(t_jc_tag tag, int mode);
t_jc_job		*jc_get_by_pid(pid_t pid);

#endif
