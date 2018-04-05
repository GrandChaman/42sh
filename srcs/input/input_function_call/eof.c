/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:28:22 by fbertoia          #+#    #+#             */
/*   Updated: 2018/02/20 13:28:24 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		sh21_eof(t_input *input)
{
	delete_forw(input);
	if (input->mode == HEREDOC && !*input->buff)
	{
		goto_end_of_prompt(input);
		input->signal = SIGNAL_CTRLD;
		return (1);
	}
	else if (input->mode == REGULAR && !*input->buff)
		ft_exit(0, NULL);
	return (0);
}
