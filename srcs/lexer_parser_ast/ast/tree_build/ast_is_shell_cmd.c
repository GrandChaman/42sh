/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_shell_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:06:25 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/24 19:14:18 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int						ast_is_shell_cmd(t_token_type type)
{
	if (type == WORD)
		return (1);
	else if (type == ASSIGNMENT_WORD)
		return (2);
	else if (type == PIPE)
		return (3);
	else if (type == While)
		return (4);
	else if (type == If)
		return (5);
	else if (type == Until)
		return (6);
	else if (type == Bang)
		return (7);
	else
		return (0);
}
