/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:36:08 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/13 14:04:12 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"

static int		get_next_quote(char *argv, char quote)
{
	int i;

	i = 1;
	while (argv[i] && argv[i] != quote)
		i++;
	if (argv[i])
		i++;
	return (i);
}

static void		case_whitespace(char **argv, int *wd_nb, int *flag)
{
	while (is_whitespace(**argv))
		(*argv)++;
	if (*flag)
		(*wd_nb)++;
	*flag = 0;
}

static int		word_number(char *argv)
{
	int wd_nb;
	int flag;

	flag = 0;
	wd_nb = 0;
	while (*argv)
	{
		if (*argv == (char)'\'' || *argv == (char)'\"')
		{
			argv += get_next_quote(argv, *argv);
			flag = 1;
		}
		else if (is_whitespace(*argv))
			case_whitespace(&argv, &wd_nb, &flag);
		else
		{
			while (!is_whitespace(*argv) && ft_isprint(*argv) && *argv
			!= (char)'\'' && *argv != (char)'\"')
				argv++;
			flag = 1;
		}
	}
	return (wd_nb + flag);
}

char			*word(char **argv)
{
	char	*ret;
	int		i;
	char	quote;
	int		flag;

	ret = NULL;
	i = 0;
	flag = 0;
	while ((*argv)[i] && ft_isprint((*argv)[i]) && !is_whitespace((*argv)[i]))
	{
		if ((*argv)[i] == (char)'\'' || (*argv)[i] == (char)'\"')
		{
			quote = (*argv)[i];
			ft_memmove(*argv + i, *argv + i + 1, ft_strlen(*argv + i + 1));
			while ((*argv)[i] && (*argv)[i] != quote)
				++i;
			ft_memmove(*argv + i, *argv + i + 1, ft_strlen(*argv + i));
		}
		else
			i++;
	}
	ret = ft_strndup(*argv, i + 1);
	*argv += i;
	return (ret);
}

char			**split_args(char *argv)
{
	char	**ret;
	int		wd_nb;
	int		i;

	i = 0;
	wd_nb = word_number(argv);
	if (!(ret = (char**)malloc(sizeof(char*) * (wd_nb + 1))))
	{
		ft_error(errno, "malloc");
		return (NULL);
	}
	while (*argv && i < wd_nb)
	{
		while (*argv && is_whitespace(*argv))
			argv++;
		ret[i++] = word(&argv);
	}
	ret[i] = NULL;
	return (ret);
}
