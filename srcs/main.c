/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:26:22 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/16 14:57:00 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"
#include "lexer.h"
#include "cli.h"

t_lex		*g_err_lex;

static void	ignore_signal(int sig)
{
	(void)sig;
}

int			main(void)
{
	t_ft_sh			*shell;
	char			*cmd;
	int				fb;
	t_sh21			*sh21;
	extern char		**environ;

	fb = 0;
	sh21 = sh21_init(environ);
	shell = get_ft_shell();
	shell->ht = NULL;
	signal(SIGINT, ignore_signal);
	if (!is_env_correct())
		return (1);
	cli_loader(0);
	if (!shell->is_a_tty)
	{
		cli_loader(1);
		return (1);
	}
	while (42)
	{
		if (((cmd = read_command(NULL, 0, 0, (!fb ? fb++ : fb))) == NULL))
			break ;
		sh21->buf = cmd;
		lexer(sh21);
		if (parser(sh21->lex) && sh21->signal != T_CTRL_C)
			sh21_get()->ret = exec_tree(sh21->tree.root_node);
		add_to_history(shell, cmd);
		del_sh21();
		free(cmd);
	}
	del_sh21_exit();
	return (0);
}
