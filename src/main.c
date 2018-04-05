/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:40:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/05 16:21:30 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	ignore_signal(int sig)
{
	(void)sig;
}

char		*check_correct(char *toto)
{
	if (!ft_strcmp(toto, "Salut"))
		return ("HeyThere > ");
	return (NULL);
}

int			main(void)
{
	t_ft_sh *shell;
	char	*cmd;
	int		should_exit;
	int		fb;

	fb = 0;
	should_exit = 0;
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
	while (!should_exit)
	{
		//char		*read_command(char *prompt, int status, int heredoc, int fb)
		//@param	char *prompt : Un prompt alternatif (au lieu d'afficher le cwd)
		//@param	int status : La valeur de retour de la derniere commande
		//@param	heredoc : Si le prompt actuel est un heredoc (Laisser *prompt a NULL si heredoc est egale a 1)
		//@param	fb : (boolean) Si le CLI doit afficher un feedback (Genre OK en vert ou Stop en rouge)
		cmd = read_command(NULL, 0, 0, (!fb ? fb++ : fb));
		ft_printf("Typed : %s\n", cmd);
		add_to_history(shell, cmd); // ADD TO HISTORY
		if (!ft_strcmp(cmd, "exit"))
			should_exit = 1;
		free(cmd);
	}
	cli_loader(1); //1 = destroying the cli
	return (0);
}
