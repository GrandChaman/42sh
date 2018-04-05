/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:24:26 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/15 15:01:29 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*find_var(char *str)
{
	char	c;
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = skip_var(str);
	c = str[j];
	str[j] = 0;
	ret = ft_getenv(str, &sh21_get()->env.orig_env);
	if (!ret)
		ret = ft_getenv(str, &sh21_get()->env.local_var);
	str[j] = c;
	str += j;
	return (ret);
}
