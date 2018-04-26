/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:07:38 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/24 15:22:34 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char *create_rdm_file(void)
{
	char	*random_file;
	char	*random_file_path;

	if (!(random_file = random_str(SIZE_RANDOM_STR)))
		return (NULL);
	if (!(random_file_path = ft_strjoin(TMP_PATH_RANDOM, random_file)))
		return (NULL);
	ft_strdel(&random_file);
	return (random_file_path);
}

static void on_subshell3(t_lexa *lexa, char *new_str)
{
	char	**arr;
	int		i;

	i = 0;
	if (lexa->oquote)
		lexa->buffer = ft_strfjoin(lexa->buffer, new_str);
	else
	{
		i = 0;
		arr = ft_split_whitespaces(new_str);
		while (arr && arr[i])
		{
			lexa->buffer = ft_strfjoin(lexa->buffer, arr[i++]);
			lexa->buffer = ft_strfjoin(lexa->buffer, " ");
		}
		del_arr(&arr);
	}
	ft_strdel(&new_str);
}

static void on_subshell2(t_lexa *lexa, char *rdm_file_io, int fd)
{
	char	buf[100];
	char	*new_str;
	int 	i;

	i = 0;
	new_str = NULL;
	while ((i = read(fd, buf, 99)) > 0)
	{
		buf[i] = '\0';
		new_str = ft_strfjoin(new_str, buf);
	}
	if (i < 0 || !new_str)
		return ;
	unlink(rdm_file_io);
	ft_strdel(&rdm_file_io);
	return (on_subshell3(lexa, new_str));
}

void 	on_subshell(t_lexa *lexa)
{
	int		offset;
	int		fd;
	char	*ret;
	char 	*rdm_file_io;

	if (lexa->buffer && lexa->buffer[0] && lexa->t != WORD)
		add_elem_back((void**)&lexa->lex, (void*)lex_create(lexa->t, lexa->buffer));
	lexa->t = WORD;
	lexa->str += 1;
	if ((offset = ft_strindex(lexa->str, '`')) < 0)
		return ;
	rdm_file_io = create_rdm_file();
	ret = ft_strndup(lexa->str, offset + 1);
	lexa->str += offset;
	exec_subshell(ret, rdm_file_io);
	ft_strdel(&ret);
	if ((fd = open(rdm_file_io, O_RDONLY)) < 0)
		return ;
	else
		return (on_subshell2(lexa, rdm_file_io, fd));
}
