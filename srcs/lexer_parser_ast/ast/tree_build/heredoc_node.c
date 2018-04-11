/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:25:16 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 14:25:18 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"
#include "ft_sh.h"

static int		final_heredoc(char *tmp, char *str, char *tmp2, int fd, t_sh21 *sh21)
{
	while ((ft_strcmp(str, tmp) != 0) && tmp[0] != T_CTRL_D)
	{
		tmp2 = ft_strjoin(tmp, "\n");
		ft_fprintf(fd, tmp2);
		free(tmp2);
		free(tmp);
		if ((tmp = read_command(NULL, 0, 1, 0)) == NULL)
		{
			free(str);
			sh21->signal = SIGNAL_CTRLC;
			return (-1);
		}
	}
	free(tmp);
	free(str);
	return (1);
}

static void		open_heredoc_file(char *path_file, int *fd)
{
	if ((*fd = open(path_file, O_WRONLY | O_TRUNC, 0777)) == -1)
		ft_perror("21sh", "Can't open heredoc file");
	close(*fd);
	if ((*fd = open(path_file, O_RDWR | O_APPEND, 0777)) == -1)
		ft_perror("21sh", "Can't open heredoc file");
}

void		heredoc_node(t_ast_node *node)
{
	char	*str;
	char	*tmp;
	char	*path_file;
	int		fd;
	char	*tmp2;
	char	*tmp_file;
	t_sh21	*sh21;

	sh21 = sh21_get();
	str = node->content;
	if (!(tmp_file = random_str(SIZE_RANDOM_STR)))
		return ;
	node->content = ft_strjoin(TMP_PATH_HEREDOC, tmp_file);
	if ((tmp = read_command(NULL, 0, 1, 0)) == NULL)
	{
		free(str);
		sh21->signal = SIGNAL_CTRLC;
		return ;
	}
	tmp2 = ft_itoa(1);
	path_file = ft_strjoin(TMP_PATH_HEREDOC, tmp_file);
	free(tmp_file);
	free(tmp2);
	if ((fd = open(path_file, O_RDWR | O_CREAT | O_EXCL |
		O_APPEND, 0777)) == -1)
		open_heredoc_file(path_file, &fd);
	free(path_file);
	if ((final_heredoc(tmp, str, tmp2, fd, sh21)) == -1)
		return ;
	close(fd);
	return ;
}
