/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:29:44 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/06 23:09:42 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		add_history_file(t_input *input, char *command)
{
	if (*command && input->history_fd >= 0)
	{
		ft_fprintf(input->history_fd, "%d %s\n",
		input->history_line_nb, command);
		input->history_line_nb++;
	}
}

t_dlinked	*add_history_list(char *command)
{
	t_dlinked	*elem;
	int			ret;

	elem = (t_dlinked*)malloc(sizeof(t_dlinked));
	if (!elem)
		ft_exit(errno, NULL);
	ret = ft_strindex(command, '\n');
	if (*command)
		elem->command = ft_strndup(command, ret > 0 ? ret + 1 :
			ft_strlen(command) + 1);
	else
		elem->command = NULL;
	elem->next = NULL;
	elem->previous = NULL;
	return (elem);
}
