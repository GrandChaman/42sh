/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:24:40 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/16 15:00:56 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int	skip_var(char *str)
{
	int		i;

	i = 0;
	if (ft_strindex(SPECIAL_PARAMETERS, str[0]) >= 0)
		i++;
	else
	{
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
	}
	return (i);
}
