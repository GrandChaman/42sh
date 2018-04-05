/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 20:22:11 by bluff             #+#    #+#             */
/*   Updated: 2017/12/22 13:11:48 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	void *res;

	if (!(res = malloc(size + 1)))
		ft_perror("malloc", "Mallocation failed. Aborting");
	ft_memset(res, '\0', size + 1);
	return (res);
}
