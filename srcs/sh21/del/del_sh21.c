/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_sh21.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:51:14 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/16 14:55:22 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	del_sh21(void)
{
	t_sh21	*sh21;

	sh21 = sh21_get();
	sh21->signal = 0;
	del_arr(&sh21->env.env_cpy);
	del_arr(&sh21->argv);
	ft_strdel(&g_err_lex->content);
	del_list((void**)&sh21->lex, del_lex);
	del_ast(&sh21->tree.root_node);
	del_list((void**)&sh21->tree.fd_cleanup, del_redir);
}

void	del_sh21_exit(void)
{
	t_sh21	*sh21;

	sh21 = sh21_get();
	del_sh21();
	del_arr(&sh21->env.orig_env);
	del_arr(&sh21->env.local_var);
	del_hash(&sh21->env);
	del_list((void**)&g_err_lex, del_lex);
	del_list((void**)&g_end_of_input, del_lex);
	close(sh21_get()->debug_tty);
	cli_loader(1);
}
