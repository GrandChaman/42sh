/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:38:21 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/26 13:49:21 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh21.h"
#include "cli.h"

void	ignore_signal(int sig)
{
	(void)sig;
}

void	signal_c(int sig)
{
	(void)sig;
	sh21_get()->signal = T_CTRL_C;
}

void	set_up_default_signal(void)
{
	signal(SIGINT, signal_c);
	signal(SIGTSTP, ignore_signal);
	signal(SIGCONT, ignore_signal);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
}
