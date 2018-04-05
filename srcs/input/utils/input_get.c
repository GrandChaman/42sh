/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:41:59 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/13 15:50:42 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			show_prompt(t_input *input)
{
	if (sh21_get()->ret < 0)
		ft_fprintf(input->tty, "%s", input->prompt);
	else if (sh21_get()->ret == 0)
		ft_fprintf(input->tty, "%[GRN]%s%[NC]", input->prompt);
	else
		ft_fprintf(input->tty, "%[RED]%s%[NC]", input->prompt);
}

static int		ft_read(t_input *input)
{
	int ret;

	if (!input->flag_prompt)
	{
		show_prompt(input);
		input->flag_prompt = 1;
	}
	ret = read(0, (char*)&input->read, BUFF_SIZE_READ);
	if (ret < 0)
		ft_error(errno, "read");
	return (1);
}

int				input_get(t_input *input)
{
	while (ft_read(input))
	{
		if (input_call_function(input))
			break ;
		input->read = 0ull;
	}
	return (1);
}
