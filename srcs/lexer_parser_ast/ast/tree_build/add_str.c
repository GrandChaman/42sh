/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:24:21 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/19 12:43:56 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_str(char **ret, char **ptr, int *i)
{
	*ret = ft_strffjoin(*ret, ft_strndup(*ptr, *i + 1));
	*ptr += *i;
	*i = 0;
	return (*ret);
}
