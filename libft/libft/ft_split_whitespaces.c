/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 16:12:08 by vbaudot           #+#    #+#             */
/*   Updated: 2018/04/22 16:18:03 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	fill_tab(char *src, char *dest, int i, int n)
{
	int o;
	int p;

	o = 0;
	p = n;
	while (o < i - n)
	{
		dest[o] = src[p];
		o++;
		p++;
	}
	dest[o] = '\0';
}

static int	iplusplus(int y, char *str, int i)
{
	if (y == 1)
	{
		while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
			i++;
	}
	else
	{
		while (!(str[i] == ' ' || str[i] == '\n'
					|| str[i] == '\t' || str[i] == '\0'))
			i++;
	}
	return (i);
}

static int	calc_nb_words(char *str)
{
	int i;
	int nb;

	nb = 0;
	i = 0;
	while (str[i] != '\0')
	{
		i = iplusplus(1, str, i);
		if (str[i] == '\0')
			break ;
		i = iplusplus(0, str, i);
		if (str[i] == '\0')
		{
			nb++;
			break ;
		}
		if (str[i] != '\0')
		{
			nb++;
		}
		i++;
	}
	nb++;
	return (nb);
}

static char	**ft_deux_split_whitespaces(int i, char *str)
{
	char	**tab;
	int		tv[2];

	tv[0] = 0;
	tv[1] = 0;
	tab = ft_memalloc(calc_nb_words(str) * sizeof(char*));
	while (str[i] != '\0')
	{
		i = iplusplus(1, str, i);
		if (str[i] == '\0')
			break ;
		tv[0] = i;
		if (str[i] != '\0')
		{
			i = iplusplus(0, str, i);
			tab[tv[1]] = ft_memalloc(sizeof(char) * ((i - tv[0]) + 1));
			fill_tab(str, tab[tv[1]], i, tv[0]);
			tv[1]++;
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	tab[tv[1]] = 0;
	return (tab);
}

char		**ft_split_whitespaces(char *str)
{
	return (ft_deux_split_whitespaces(0, str));
}
