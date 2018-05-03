/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_multi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:20:50 by bluff             #+#    #+#             */
/*   Updated: 2017/12/22 13:59:23 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int			count_words(const char *s, int (*c)(int))
{
	int		count;
	int		i;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (c(s[i]))
		i++;
	while (s[i++])
	{
		if (c(s[i - 1]) && in_word)
		{
			count++;
			in_word = 0;
		}
		else if (!c(s[i - 1]))
			in_word = 1;
	}
	if (in_word)
		count++;
	return (count);
}

static char			**split_routine(char **res, const char *s, int (*c)(int))
{
	int start;
	int pos;
	int i;
	int in_word;

	in_word = 0;
	start = 0;
	pos = 0;
	i = -1;
	while (s[++i])
	{
		if (c(s[i]) && in_word)
		{
			in_word = 0;
			res[pos++] = ft_strsub(s, start, i - start);
		}
		else if (!c(s[i]) && !in_word)
		{
			in_word = 1;
			start = i;
		}
	}
	if (in_word)
		res[pos] = ft_strsub(s, start, i - start);
	return (res);
}

char				**ft_strsplit_multi(const char *s, int (*c)(int))
{
	char	**res;
	int		nb_words;

	if (!s)
		return (NULL);
	nb_words = count_words(s, c);
	if (!(res = (char**)malloc(sizeof(char*) * (nb_words + 1))))
		ft_perror("malloc", "Mallocation failed. Aborting");
	res[nb_words] = NULL;
	split_routine(res, s, c);
	return (res);
}
