/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:31:32 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/20 18:24:13 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			handle_sigint(int sig)
{
	const char	tmp[] = "\n";

	if (sh21_get()->script)
	{
		del_sh21_exit();
		exit(1);
	}
	ioctl(0, TIOCSTI, tmp);
	(void)sig;
}

void			handle_windowsize(int nb)
{
	t_sh21 *sh21;

	(void)nb;
	sh21 = sh21_get();
	ioctl(0, TIOCGWINSZ, &sh21->input.winsize);
	if (sh21->input.in)
	{
		clear_command(&sh21->input);
		display_input(&sh21->input);
		rt_cursor(&sh21->input);
	}
}

void			handle_sigterm(int nb)
{
	(void)nb;
	reinit_term(sh21_get());
	ft_exit(0, NULL);
}

int				all_signal(void)
{
	signal(SIGWINCH, handle_windowsize);
	signal(SIGINT, handle_sigint);
	signal(SIGTERM, handle_sigterm);
	return (0);
}
