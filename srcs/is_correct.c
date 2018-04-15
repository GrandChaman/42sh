
#include "sh21.h"

static int check_second_quote(char second, int *i, char *cmd)
{
	*i = *i + 1;
	while (cmd[*i] && cmd[*i] != second)
		*i = *i + 1;
	if (cmd[*i] == '\0')
		return (1);
	return (0);
}

static int quote(char *cmd, int *i)
{
	char tabl[4];
	int var;

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

char		*check_correct(char *cmd){
	int i;
	int stock;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
		{
			i++;
			if (cmd[i] == '\0')
				continue ;
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
		if (cmd[i] && (cmd[i] == '|' || cmd[i] == '\\'))
		{
			stock = cmd[i];
			i++;
			while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\n'))
				i++;
			if (cmd[i] == '\0')
			{
				if (stock == '|')
					return ("pipe>");
				if (stock == '\\')
					return ("backslash>");
			}
		}
		i++;
	}
	return (NULL);
}