/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:39:00 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/21 11:39:07 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		controlk_bis(t_input *input, char *cc)
{
	input->buff_len = ft_strlen(input->buff);
	input->cur_pos = input->start_select;
	input->start_select = -1;
	input->end_select = -1;
	input->clipboard = ft_strdup(cc);
}

int				controlk(t_input *input)
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
	while (i++ < input->end_select + 1 && input->buff[input->start_select])
	{
		cc[ci++] = input->buff[input->start_select];
		input->buff = ft_strpop(input->buff, input->start_select);
	}
	cc[ci] = 0;
	controlk_bis(input, cc);
	ft_strdel(&cc);
	return (0);
}
