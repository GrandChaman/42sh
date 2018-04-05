/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:30:28 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/03 17:00:21 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	init_prompt(t_input *input, char c)
{
	char			buf[PATH_MAX];
	char			*pwd = ft_getenv("PWD", &sh21_get()->env.orig_env);
	t_sh21			*sh21;

	ft_bzero(buf, PATH_MAX);
	sh21 = sh21_get();
	ft_strcpy(buf, pwd);
	if (ft_strnequ(buf, ft_getenv("HOME",
	&sh21_get()->env.orig_env), ft_strlen(ft_getenv("HOME",
	&sh21_get()->env.orig_env))))
	{
		ft_memmove(buf + 1, buf + ft_strlen(ft_getenv("HOME",
		&sh21_get()->env.orig_env)), ft_strlen(buf +
			ft_strlen(ft_getenv("HOME", &sh21_get()->env.orig_env) + 1)));
		buf[0] = '~';
	}
	if (input->prompt)
		ft_memdel((void**)&input->prompt);
	if (!c)
		input->prompt = ft_strjoin(buf, " $>_ ");
	else if (c == '\'')
		input->prompt = ft_strdup("quote> ");
	else if (c == '\"')
		input->prompt = ft_strdup("dquote> ");
	else if (c == 'h')
		input->prompt = ft_strdup("heredoc> ");
}

void	clear_history(t_input *input)
{
	ft_strdel(&input->historic_buff);
	input->history.needle = NULL;
}

void	input_init(t_input *input, char c)
{
	input->cur_pos = 0;
	input->prompt_sz = 0;
	input->buff_len = 0;
	input->start_select = -1;
	input->end_select = -1;
	input->is_select = 0;
	if (input->buff)
		ft_memdel((void**)&input->buff);
	input->buff = ft_strnew(BUFF_SIZE_INPUT_21SH);
	input->buff_sz = BUFF_SIZE_INPUT_21SH;
	init_prompt(input, c);
	clear_history(input);
	input->prompt_sz = ft_strlen(input->prompt);
	input->in = 1;
	input->history.needle = NULL;
	input->flag_prompt = 0;
	input->last_mv = 0;
	input->mode = REGULAR;
	input->signal = SIGNAL_NONE;
}
