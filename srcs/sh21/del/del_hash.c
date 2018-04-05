/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:50:49 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 14:50:50 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	del_hash_bin(t_hash_bin *hash_bin)
{
	(hash_bin->path) ? ft_strdel(&hash_bin->path) : (0);
	if (hash_bin->next)
	{
		del_hash_bin(hash_bin->next);
		free(hash_bin->next);
		hash_bin->next = NULL;
	}
}

void	del_hash(t_env *env)
{
	int	idx;

	idx = 0;
	while (idx < HASH_SIZE)
	{
		if (env->hash_table[idx].path)
		{
			del_hash_bin(&env->hash_table[idx]);
			ft_bzero(&env->hash_table[idx], sizeof(t_hash_bin));
		}
		++idx;
	}
}
