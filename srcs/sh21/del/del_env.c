/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:50:43 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/14 21:10:52 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	del_flist(void **lst)
{
	t_list **elem;

	elem = (t_list**)lst;
	ft_memdel(&(*elem)->content);
	ft_memdel(lst);
}
