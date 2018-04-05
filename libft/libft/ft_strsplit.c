/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:20:50 by bluff             #+#    #+#             */
/*   Updated: 2017/12/22 13:11:57 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int			count_words(const char *s, char c)
{
	int		count;
	int		i;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i] == c)
		i++;
	while (s[i++])
	{
		if (s[i - 1] == c && in_word)
		{
			count++;
			in_word = 0;
		}
		else if (s[i - 1] != c)
			in_word = 1;
	}
	if (in_word)
		count++;
	return (count);
}

static char			**split_routine(char **res, const char *s, char c)
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
		if (s[i] == c && in_word)
		{
			in_word = 0;
			res[pos++] = ft_strsub(s, start, i - start);
		}
		else if (s[i] != c && !in_word)
		{
			in_word = 1;
			start = i;
		}
	}
	if (in_word)
		res[pos] = ft_strsub(s, start, i - start);
	return (res);
}

char				**ft_strsplit(const char *s, char c)
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
