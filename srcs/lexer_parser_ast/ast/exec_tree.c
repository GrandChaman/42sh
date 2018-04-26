/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:26:30 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/26 14:27:36 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh21.h"

int	exec_tree(t_ast_node *first)
{
	int		ret;
	t_sh21	*sh21;

	sh21 = sh21_get();
	if (sh21->signal == T_CTRL_C)
		return (1);
	sh21->signal = 0;
	ret = g_exec_fn[first->type](first);
	return (ret);
}
