/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:28:36 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/21 17:52:53 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static char		check_next_quote(char *str, int *i, char quote)
{
	int j;

	j = *i + 1;
	while (str[j])
	{
		*i = j;
		if (str[j] == quote)
			return (0);
		j++;
	}
	return (quote);
}

static char		quote_parser(t_input *input, char quote)
{
	int i;

	i = -1;
	if (quote)
		quote = check_next_quote(input->buff, &i, quote);
	while (!quote && input->buff[++i])
	{
		if (input->buff[i] == '\"' || input->buff[i] == '\'')
			quote = check_next_quote(input->buff, &i, input->buff[i]);
	}
	return (quote);
}

static int		newline_quote(t_input *input, char quote)
{
	input->buff = ft_strpush(input->buff, input->buff_len,
		'\n', &input->buff_sz);
	input->tmp_buff = ft_strfjoin(input->tmp_buff, input->buff);
	input_init(input, quote);
	return (0);
}

static int		newline_eofcommand(t_input *input)
{
	input->buff = ft_strffjoin(input->tmp_buff, input->buff);
	input->tmp_buff = NULL;
	if (input->buff && *input->buff)
		add_elem_front_dl((void**)&input->history.list,
			add_history_list(input->buff));
	add_history_file(input, input->buff);
	input->in = 0;
	return (1);
}

int				sh21_newline(t_input *input)
{
	input->flag_prompt = 0;
	if (input->is_select)
	{
		input->start_select = -1;
		input->end_select = -1;
		clear_command(input);
		sv_cursor(input, input->buff_len, input->cur_pos);
		display_input(input);
		rt_cursor(input);
	}
	goto_end_of_prompt(input);
	if (input->mode == REGULAR)
	input->quote = quote_parser(input, input->quote);
	if (input->quote && input->mode == REGULAR)
		return (newline_quote(input, input->quote));
	else
		return (newline_eofcommand(input));
}
