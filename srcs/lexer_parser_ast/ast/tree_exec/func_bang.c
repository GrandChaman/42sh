/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_bang.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:59:29 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/24 19:13:35 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh21.h"

int		func_bang(t_ast_node *root)
{
	int status;

	status = g_exec_fn[root->left->type](root->left);
	return (!status);
}
