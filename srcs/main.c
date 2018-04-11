/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:26:22 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/06 17:16:22 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"
#include "lexer.h"
#include "ft_sh.h"

t_lex		*g_err_lex;

static void	ignore_signal(int sig)
{
	(void)sig;
}

int			main(void)
{
	t_ft_sh *shell;
	char	*cmd;
	int		fb;
	t_sh21			*sh21;
	extern char		**environ;

	fb = 0;
	sh21 = sh21_init(environ);
	shell = get_ft_shell();
	shell->ht = NULL; //HASH TABLE
	signal(SIGINT, ignore_signal);
	if (!is_env_correct()) //CHECK ENV
		return (1);
	cli_loader(0); //0 = loading the cli
	if (!shell->is_a_tty)
	{
		cli_loader(1); //1 = destroying the cli
		return (1);
	} 
	while (42)
	{
		//char		*read_command(char *prompt, int status, int heredoc, int fb)
		//@param	char *prompt : Un prompt alternatif (au lieu d'afficher le cwd)
		//@param	int status : La valeur de retour de la derniere commande
		//@param	heredoc : Si le prompt actuel est un heredoc (Laisser *prompt a NULL si heredoc est egale a 1)
		//@param	fb : (boolean) Si le CLI doit afficher un feedback (Genre OK en vert ou Stop en rouge)
		cmd = read_command(NULL, 0, 0, (!fb ? fb++ : fb));
		sh21->buf = cmd;
		lexer(sh21);
		if (parser(sh21->lex) && sh21->signal != SIGNAL_CTRLC)
			sh21_get()->ret = exec_tree(sh21->tree.root_node);
		add_to_history(shell, cmd); // ADD TO HISTORY
		free(cmd);
	}
	cli_loader(1); //1 = destroying the cli
	return (0);
}
