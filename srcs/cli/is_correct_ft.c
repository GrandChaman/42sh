/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_correct_ft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 14:58:30 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/25 14:58:32 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char			*return_prompt(int stock)
{
	if (stock == 1)
		return ("d_quote> ");
	else if (stock == 2)
		return ("s_quote> ");
	else
		return ("b_quote> ");
}

static void		bracket_loop(char *cmd, int i, int tabl[3])
{
	if (cmd[i] == '{' && (i == 0 || cmd[i - 1] != '\\'))
		tabl[0]++;
	else if (cmd[i] == '}' && (i == 0 || cmd[i - 1] != '\\'))
		tabl[0]--;
	else if (cmd[i] == '(' && (i == 0 || cmd[i - 1] != '\\'))
		tabl[1]++;
	else if (cmd[i] == ')' && (i == 0 || cmd[i - 1] != '\\'))
		tabl[1]--;
	else if (cmd[i] == '[' && (i == 0 || cmd[i - 1] != '\\'))
		tabl[2]++;
	else if (cmd[i] == ']' && (i == 0 || cmd[i - 1] != '\\'))
		tabl[2]--;
}

char			*bracket(char *cmd, int i)
{
	int tabl[3];

	tabl[0] = 0;
	tabl[1] = 0;
	tabl[2] = 0;
	while (cmd[++i])
	{
		quote(cmd, &i);
		if (!cmd[i])
			return (NULL);
		bracket_loop(cmd, i, tabl);
	}
	if (tabl[0] > 0)
		return ("need_}> ");
	else if (tabl[1] > 0)
		return ("need_)> ");
	else if (tabl[2] > 0)
		return ("need_]> ");
	return (NULL);
}
