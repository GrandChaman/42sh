/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:01:39 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/15 18:01:04 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del_arr(char ***arr)
{
	int i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while ((*arr)[i])
	{
		ft_memdel((void**)&(*arr)[i]);
		i++;
	}
	ft_memdel((void**)&(*arr));
}
