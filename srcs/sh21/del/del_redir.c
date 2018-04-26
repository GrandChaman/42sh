/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:51:09 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 14:51:12 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	del_heredocs(void *content, size_t size)
{
	(void)size;
	if (content)
	{
		unlink((char*)content);
		ft_strdel((char**)&content);
	}
}

void	del_redir(void **node)
{
	ft_memdel(node);
	return ;
}
