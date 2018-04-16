/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_correct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:02:35 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/16 15:02:55 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int	check_second_quote(char second, int *i, char *cmd)
{
	*i = *i + 1;
	while (cmd[*i] && cmd[*i] != second)
	{
		if (cmd[*i] == '\\')
		{
			*i = *i + 1;
			if (cmd[*i] == '\0')
				continue ;
			*i = *i + 1;
			continue ;
		}
		*i = *i + 1;
	}
	if (cmd[*i] == '\0')
		return (1);
	return (0);
}

static int	quote(char *cmd, int *i)
{
	char	tabl[4];
	int		var;

	tabl[1] = '"';
	tabl[2] = '\'';
	tabl[3] = '\0';
	var = 1;
	while (tabl[var])
	{
		if (cmd[*i] == tabl[var])
		{
			if ((check_second_quote(tabl[var], i, cmd)) != 0)
				return (var);
		}
		var++;
	}
	return (0);
}

static char	*check_correct_2(int i, char *cmd)
{
	int		o;
	int		stock;
	int		beforestock;

	if (cmd[i] && (cmd[i] == '|' || cmd[i] == '\\' || cmd[i] == '&'))
	{
		stock = cmd[i];
		if (cmd[i - 1])
			beforestock = cmd[i - 1];
		o = i;
		o++;
		while (cmd[o] && (cmd[o] == ' ' || cmd[o] == '\n'))
			o++;
		if (cmd[o] == '\0')
		{
			if (stock == '|')
				return ("cmd>");
			else if (stock == '\\')
				return ("cmd");
			else if (stock == '&' && beforestock && beforestock == '&')
				return ("cmd>");
		}
	}
	return (NULL);
}

char		*check_correct(char *cmd)
{
	int		i;
	int		stock;
	char	*retour;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\\')
		{
			if (cmd[++i] == '\0')
				return ("cmd>");
			i++;
			continue ;
		}
		if ((stock = quote(cmd, &i)) != 0)
		{
			if (stock == 1)
				return ("d_quote>");
			if (stock == 2)
				return ("s_quote>");
		}
		if ((retour = check_correct_2(i, cmd)) != NULL)
			return (retour);
	}
	return (NULL);
}
