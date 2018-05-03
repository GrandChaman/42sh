/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:31:31 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/19 13:29:35 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

static void		insert_normal_touch(t_ft_sh *sh)
{
	if (!sh->is_a_tty)
		return ;
	sh->cursor--;
	update_stdout(sh, 0);
}

void			print_normal_touch(t_ft_sh *sh, unsigned long rchar)
{
	dbuf_insert(&sh->buf, sh->cursor++, (char)rchar);
	if (sh->cursor < sh->buf.cursor)
		insert_normal_touch(sh);
	else if (sh->is_a_tty)
	{
		ft_putchar((char)rchar);
		if (((sh->prompt_size +
			(sh->cursor - sh->alt_cursor)) % (sh->x_size)) == 0)
			ft_putchar('\n');
	}
}
