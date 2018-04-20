/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:07:38 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/19 19:46:28 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"

// change_fd();


char	*exec_subshell(char *str)
{
	//t_ast *root;
	int		cmd_fd;
	int		res_fd;
	int		nw;
	int		nerr;
	pid_t	pid;
	char	*argv[] = {"./42sh", ".42sh_subshell_cmd0", NULL};

	cmd_fd = open(".42sh_subshell_cmd0", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	write(cmd_fd, str, ft_strlen(str));
	close(cmd_fd);
	res_fd = open(".42sh_subshell_res0", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	nw = dup(1);
	nerr = dup(2);
	dup2(res_fd, 1);
	close(2);
	pid = fork();
	if (pid == 0)
	{
		execve("./42sh", argv, sh21_get()->env.orig_env);
	}
	else
	{
		wait(&pid);
		dup2(nerr, 2);
		dup2(nw, 1);
	}
	return (str);
}

void	on_magicq(t_lexa *lexa)
{
	int		offset;
	char	*ret;
	int		fd;
	char	buf[100];
	char	**arr;
	char	*new_str;
	int		i;

	if (lexa->buffer && lexa->buffer[0] && lexa->t != WORD)
		add_elem_back((void**)&lexa->lex, (void*)lex_create(lexa->t, lexa->buffer));
	lexa->t = WORD;
	offset = ft_strindex(lexa->str + 1, '`');
	if (offset < 0)
		return ;
	lexa->str++;
	ret = ft_strndup(lexa->str, offset + 1);
	lexa->str += offset;
	exec_subshell(ret);
	ft_strdel(&ret);
	fd = open(".42sh_subshell_res0", O_RDONLY);
	new_str = NULL;
	ft_printf("3 str = %s\n", lexa->str);

	while ((i = read(fd, buf, 99)) > 0)
	{
		buf[i] = '\0';
		new_str = ft_strfjoin(new_str, buf);
	}
	if (!new_str)
		return ;
	if (lexa->oquote)
		lexa->buffer = ft_strfjoin(lexa->buffer, new_str);
	else
	{
		arr = ft_split_whitespaces(new_str);
		i = 0;
		while (arr && arr[i])
		{
			lexa->buffer = ft_strfjoin(lexa->buffer, arr[i]);
			lexa->buffer = ft_strfjoin(lexa->buffer, " ");
			i++;
		}
		del_arr(&arr);
	}
	ft_printf("4 str = %s\n", lexa->str);

	ft_strdel(&new_str);
}
