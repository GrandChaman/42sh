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

void		heredoc_node2(t_input *input, int fd)
{
	if (input->buff)
	{
		write(fd, input->buff, ft_strlen(input->buff));
		ft_putchar_fd('\n', fd);
	}
	input_init(input, 'h');
	sh21_get()->input.mode = HEREDOC;
	input_get(input);
}

void		heredoc_node(t_ast_node *node)
{
	t_input	*input;
	int		fd;
	char	*tmp_file;
	char	*tmp_heredoc;

	tmp_heredoc = node->content;
	if (!(tmp_file = random_str(SIZE_RANDOM_STR)))
		return ;
	node->content = ft_strjoin(TMP_PATH_HEREDOC, tmp_file);
	if ((fd = open(node->content, O_CREAT | O_WRONLY, 0644)) < 0)
	{
		ft_strdel(&tmp_heredoc);
		return ;
	}
	ft_strdel(&tmp_file);
	input = &sh21_get()->input;
	input_init(input, 'h');
	sh21_get()->input.mode = HEREDOC;
	init_term(sh21_get());
	while (sh21_get()->terminal.isatty && !ft_strequ(input->buff, tmp_heredoc)
	&& sh21_get()->input.signal != SIGNAL_CTRLD
	&& sh21_get()->input.signal != SIGNAL_CTRLC)
		heredoc_node2(input, fd);
	reinit_term(sh21_get());
	ft_strdel(&tmp_heredoc);
	close(fd);
}
