/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_piped_script.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:03:09 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/19 18:10:17 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			ast_print(t_ast_node *root)
{
	static int offset;

	if (!root)
		return ;
	offset += 4;
	ast_print(root->right);
	offset -= 4;
	ft_fprintf(sh21_get()->debug_tty, "%*s%s\n", offset, "", root->content);
	offset += 4;
	ast_print(root->left);
	offset -= 4;
}

static int		input_piped_script2(t_sh21 *sh21, int ret)
{
	if (ret < 0)
		ft_exit(errno, "pipe_error");
	sh21->lex = lexer(sh21->buf);
	if (parser(sh21->lex))
		exec_tree(sh21->tree.root_node);
	ft_exit(0, NULL);
	return (0);
}

int				input_piped_script(t_sh21 *sh21, char **argv)
{
	char	buf[1024 + 1];
	int		ret;
	int		fd_input;

	fd_input = 0;
	ft_bzero(buf, 1025);
	sh21->script = 1;
	if (argv[1])
	{
		if ((sh21->terminal.fd_script_shell = open(argv[1], O_RDONLY)) < 0)
			ft_exit(errno, "script_error");
		fd_input = sh21->terminal.fd_script_shell;
	}
	while ((ret = read(fd_input, buf, 1024)) > 0)
	{
		buf[ret] = 0;
		sh21->buf = ft_strfjoin(sh21->buf, buf);
	}
	if (ret < 0 || !sh21->buf)
		ft_exit(-6, "script_error");
	return (input_piped_script2(sh21, ret));
}
