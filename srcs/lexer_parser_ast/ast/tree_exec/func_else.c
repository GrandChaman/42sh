/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_else.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:19:20 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/18 23:19:22 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		func_else(t_ast_node *root)
{
	if (sh21_get()->signal == T_CTRL_C)
		return (1);
	return (g_exec_fn[root->left->type](root->left));
}
