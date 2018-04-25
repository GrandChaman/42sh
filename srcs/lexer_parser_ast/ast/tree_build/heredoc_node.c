/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <fbertoia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:25:16 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/21 19:07:41 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"
#include "cli.h"

static int	final_heredoc(char *tmp, char *str, int fd, t_sh21 *sh21)
{
	char *tmp2;

	while ((ft_strcmp(str, tmp) != 0) && tmp[0] != T_CTRL_D)
	{
		tmp2 = ft_strjoin(tmp, "\n");
		ft_fprintf(fd, tmp2);
		free(tmp2);
		free(tmp);
		if ((tmp = read_command(NULL, 0, 1)) == NULL)
		{
			free(str);
			sh21->signal = T_CTRL_C;
			close(fd);
			return (-1);
		}
	}
	free(tmp);
	free(str);
	return (1);
}

static void	open_random_file(char *path_file, int *fd)
{
	if ((*fd = open(path_file, O_WRONLY | O_TRUNC, 0777)) == -1)
		ft_perror("42sh", "Can't open heredoc file");
	close(*fd);
	if ((*fd = open(path_file, O_RDWR | O_APPEND, 0777)) == -1)
		ft_perror("42sh", "Can't open heredoc file");
}

static void	heredoc_node_2(char *str, char *tmp, char *tmp_file, t_sh21 *sh21)
{
	char	*path_file;
	int		fd;

	path_file = ft_strjoin(TMP_PATH_RANDOM, tmp_file);
	free(tmp_file);
	if ((fd = open(path_file, O_RDWR | O_CREAT | O_EXCL |
		O_APPEND, 0777)) == -1)
		open_random_file(path_file, &fd);
	free(path_file);
	if ((final_heredoc(tmp, str, fd, sh21)) == -1)
		return ;
	close(fd);
	return ;
}

void		heredoc_node(t_ast_node *node)
{
	char	*str;
	char	*tmp;
	char	*tmp_file;
	t_sh21	*sh21;

	sh21 = sh21_get();
	str = node->content;
	if (!(tmp_file = random_str(SIZE_RANDOM_STR)))
		return ;
	node->content = ft_strjoin(TMP_PATH_RANDOM, tmp_file);
	if ((tmp = read_command(NULL, 0, 1, 0)) == NULL)
	{
		free(str);
		free(tmp_file);
		sh21->signal = T_CTRL_C;
		return ;
	}
	heredoc_node_2(str, tmp, tmp_file, sh21);
	return ;
}
