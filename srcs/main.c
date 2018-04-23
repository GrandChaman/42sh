/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:26:22 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/23 14:07:04 by fle-roy          ###   ########.fr       */
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
	int		fb;
	char	*cmd;

	fb = 0;
	while (42)
	{
		if (((cmd = read_command(NULL, sh21->ret, 0, (!fb ? fb++ : fb))) == NULL))
			break ;
		cmd = remove_char(cmd);
		if (!bang(&cmd))
		{
			del_sh21();
			ft_strdel(&cmd);
			continue;
		}
		add_to_history(shell, cmd);
		sh21->buf = cmd;
		lexer(sh21);
		if (parser(sh21->lex) && sh21->signal != T_CTRL_C)
			sh21_get()->ret = exec_tree(sh21->tree.root_node);
		del_sh21();
		ft_strdel(&cmd);
	}
}

void		job_control_test(char **environ)
{
	t_jc_tag	ntag;
	pid_t		pid;
	int			status;
	char *newargv[] = { "sleep", "100", NULL };
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	pid = fork();
	if (!pid)
		exit(execve("/bin/sleep", newargv, environ));
	ntag = jc_create_tag();
	jc_add(ntag, pid);
	jc_set(ntag, FG);
	ft_printf("Juste avant le wait wefewfwe \n");
	while (1)
	{
		waitpid(-pid, &status, WUNTRACED);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGCONT, SIG_IGN);
		tcsetpgrp(0, getpgrp());
		signal(SIGTTOU, SIG_DFL);
		if (WIFSTOPPED(status))
		{
			main_loop(sh21_get(), get_ft_shell());
			break ;
		}
		break ;
	}
	jc_delete_tag(ntag);
}



int			main(void)
{
	t_ft_sh			*shell;
	t_sh21			*sh21;
	extern char		**environ;

	setlocale(LC_ALL, "");
	sh21 = sh21_init(environ);
	shell = get_ft_shell();
	shell->ht = NULL;
	signal(SIGINT, ignore_signal);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
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
	//job_control_test(environ);
	del_sh21_exit();
	return (0);
}
