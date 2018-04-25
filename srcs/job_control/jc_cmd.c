/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 14:05:09 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/25 14:05:10 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*jc_cmd(t_ast_node *node)
{
	char *ret;

	if (node->piped_cmd && node->pipe_fd[1] != 1)
		ret = ft_strjoin(node->content, " |");
	else
		ret = ft_strdup(node->content);
	return (ret);
}
