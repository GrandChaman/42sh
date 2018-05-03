/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_piped_script.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:03:09 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/18 17:58:00 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			ast_print(t_ast_node *root)
{
	static int offset;

	if (!root)
		return ;
	offset += 4;
	ast_print(root->right);
	offset -= 4;
	ft_fprintf(sh21_get()->debug_tty, "%*s%s\n", offset, "", root->content ?
	root->content : g_token_type_str[root->type]);
	ast_print(root->condition_node);
	offset += 4;
	ast_print(root->left);
	offset -= 4;
}
