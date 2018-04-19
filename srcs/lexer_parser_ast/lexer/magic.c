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
		dup2(nerr, 2);
		dup2(nw, 1);
		wait(&pid);
	}
	return (str);
}

void	on_magicq(t_lexa *lexa)
{
	int		offset;
	char	*ret;
	int		fd;
	char	c;
	int		i = 0;
	char	*new_str;
	size_t	buf = 32;

	add_elem_back((void**)&lexa->lex, (void*)lex_create(lexa->t, lexa->buffer));
	lexa->str++;
	offset = ft_strindex(lexa->str, '`');
	ret = ft_strndup(lexa->str, offset + 1);
	lexa->str += ft_strlen(ret) + 1;
	exec_subshell(ret);
	fd = open(".42sh_subshell_res0", O_RDONLY);
	new_str = ft_strdup(lexa->str);
	new_str = ft_strpush(new_str, i++, '#', &buf);
	while (read(fd, &c, 1) == 1)
	{
		//ft_putchar(c);
		if (ft_iswhitespace(c)) c = ' ';
		new_str = ft_strpush(new_str, i++, c, &buf);
		//ft_printf("--%s--\n", new_str);
	}
	lexa->str = new_str;
	//ft_printf(">>%s--\n", lexa->str);
}
