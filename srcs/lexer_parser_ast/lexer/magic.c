/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:07:38 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/19 18:27:45 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"

// change_fd();


char	*exec_subshell(char *str)
{
	//t_ast *root;
	int		fd;
	pid_t	pid;
	char	*argv[] = {"./42sh", "/tmp/subshell", NULL};

	fd = open("/tmp/subshell", O_CREAT | O_WRONLY | O_TRUNC);
	write(fd, str, ft_strlen(str));
	pid = fork();
	if (pid == 0)
		execve("./42sh", argv, sh21_get()->env.orig_env);
	else
		wait(&pid);
	return (str);
}

void	on_magicq(t_lexa *lexa)
{
	int		offset;
	char	*ret;
	int		fd;
	char	c;
	size_t	buf = 32;

	lexa->str++;
	offset = ft_strindex(lexa->str, '`');
	ret = ft_strndup(lexa->str, offset + 1);
	lexa->str += offset;
	exec_subshell(ret);
	fd = open("/tmp/subshell", O_RDONLY);
	while (read(fd, &c, 1))
		ft_strpush(lexa->str, 0, c, &buf);
	(void)lexa;
}
