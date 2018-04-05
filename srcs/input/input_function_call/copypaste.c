/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copypaste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:04:15 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/21 10:45:45 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int				set_uinput(t_input *input)
{
	input->is_select = 1;
	if (input->cur_pos >= input->buff_len)
		input->cur_pos--;
	input->start_select = input->cur_pos;
	if (input->start_select >= (int)input->buff_len)
		input->start_select--;
	input->end_select = input->start_select;
	input->last_mv = input->cur_pos;
	return (0);
}

int				delete_select(t_input *input)
{
	int		i;

	tputs(tgetstr("me", NULL), 1, my_putchar);
	input->is_select = 0;
	i = input->start_select;
	while (i++ < input->end_select + 1)
		input->buff = ft_strpop(input->buff, input->start_select);
	input->buff_len = ft_strlen(input->buff);
	input->cur_pos = input->start_select;
	input->start_select = -1;
	input->end_select = -1;
	return (0);
}

int				controlt(t_input *input)
{
	int		i;

	i = 0;
	if (input->clipboard)
	{
		while (i < (int)ft_strlen(input->clipboard))
		{
			input_putc(input, input->clipboard[i++]);
		}
		input->buff_len = ft_strlen(input->buff);
	}
	input->is_select = 0;
	input->start_select = -1;
	input->end_select = -1;
	return (0);
}

int				controle(t_input *input)
{
	char		*cc;
	int			ci;
	int			i;

	if (!(ci = 0) && (!input->buff || !*input->buff))
		return (0);
	if (!input->is_select)
		return (set_uinput(input));
	tputs(tgetstr("me", NULL), 1, my_putchar);
	input->is_select = 0;
	input->clipboard ? ft_strdel(&input->clipboard) : (0);
	cc = ft_strnew(input->end_select - input->start_select + 2);
	i = input->start_select;
	while (i < input->end_select + 1 && input->buff[i])
	{
		cc[ci] = input->buff[i];
		i++;
		ci++;
	}
	cc[ci] = 0;
	input->start_select = -1;
	input->end_select = -1;
	input->clipboard = ft_strdup(cc);
	ft_strdel(&cc);
	return (0);
}
