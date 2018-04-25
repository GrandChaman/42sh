/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:50:38 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/15 17:49:00 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void 	del_assign(void **node)
{
	t_assign_ls **tmp;

	if (!*node)
		return ;
	tmp = (t_assign_ls**)node;
	ft_strdel(&(*tmp)->assignation);
	ft_memdel(node);
}

void	del_ast(t_ast_node **node)
{
	if (!node || !*node)
		return ;
	del_ast(&(*node)->left);
	del_ast(&(*node)->right);
	del_ast(&(*node)->redir_node);
	del_ast(&(*node)->condition_node);
	del_list((void**)(&(*node)->assign_node), del_assign);
	ft_strdel(&(*node)->heredoc);
	ft_strdel(&(*node)->content);
	ft_memdel((void**)node);
}
