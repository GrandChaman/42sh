/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:26:22 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/25 14:31:41 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"
#include "lexer.h"
#include "cli.h"
#include "libft.h"
#include "job_control.h"
#include <locale.h>

t_lex		*g_err_lex;


static void	ignore_signal(int sig)
{
	(void)sig;
}

static void	main_loop(t_sh21 *sh21, t_ft_sh *shell)
{
	char	*cmd;

	while (42)
	{
		if (((cmd = read_command(NULL, sh21->ret, 0)) == NULL) &&
			jc_get()->job_list == NULL)
			break ;
		if (!cmd)
		{
			ft_fprintf(2, "Jobs are still running. Please close them before "
			"exiting\n");
			continue ;
		}
		cmd = remove_char(cmd);
		if (!bang(&cmd))
		{
			del_sh21();
			ft_strdel(&cmd);
			continue;
		}
		add_to_history(shell, cmd);
		sh21->buf = cmd;
		jc_update_all();
		sh21->lex = lexer(cmd);
		if (parser(sh21->lex) && sh21->signal != T_CTRL_C)
		{
//			ast_print(sh21->tree.root_node);
			sh21_get()->ret = exec_tree(sh21->tree.root_node);
		}
		del_sh21();
		ft_strdel(&cmd);
	}
}

int			main(int argc, char *argv[])
{
	t_ft_sh			*shell;
	t_sh21			*sh21;
	extern char		**environ;

	setlocale(LC_ALL, "");
	(void)argc;
	sh21 = sh21_init(environ);
	shell = get_ft_shell();
	shell->ht = NULL;
	if (!sh21->terminal.isatty || argv[1])
		return (input_piped_script(sh21, argv));
	signal(SIGINT, ignore_signal);
	signal(SIGTSTP, ignore_signal);
	signal(SIGCONT, ignore_signal);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	setpgid(0, getpid());
	if (!is_env_correct())
		return (1);
	cli_loader(0);
	if (!shell->is_a_tty)
	{
		cli_loader(1);
		return (1);
	}
	main_loop(sh21, shell);
	//job_control_test(sh21);
	del_sh21_exit();
	return (0);
}
