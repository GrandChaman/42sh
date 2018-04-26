/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:26:13 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/26 14:34:30 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"
#include "sh21.h"

static char				*extract_autocomplete_search(t_ft_sh *sh)
{
	int		len;
	char	*tmp;
	char	*res;

	len = 1;
	if (!sh->cursor || ft_iswhitespace(sh->buf.buf[sh->cursor - 1]))
		return (NULL);
	while (sh->cursor - len > 0 &&
			!ft_iswhitespace(sh->buf.buf[sh->cursor - len]))
		len++;
	tmp = ft_strndup2(sh->buf.buf + (sh->cursor - len) +
		(sh->cursor - len > 0), len - (sh->cursor - len > 0));
	if (tmp && tmp[0] == '~')
	{
		ft_asprintf(&res, "%s%s", ft_getenv("HOME", &sh21_get()->env.orig_env),
			tmp + 1);
		free(tmp);
		return (res);
	}
	else
		return (tmp);
}

void					collect_data(char *str_part)
{
	t_ft_sh			*sh;
	unsigned int	save_cur;
	int				max_possible_element;

	sh = get_ft_shell();
	save_cur = sh->cursor;
	max_possible_element = (sh->x_size / 8) * sh->y_size;
	collect_data_local_file(&sh->autocomplete, str_part);
	collect_data_ht(&sh->autocomplete, str_part);
	if (ft_lstsize(sh->autocomplete) >= max_possible_element)
	{
		if (sh->autocomplete)
			ft_lstdel(&sh->autocomplete, delete_autocomplete_entry);
		exec_term_command(TC_BELL);
		return ;
	}
	else
		ft_lstsort(&sh->autocomplete, cmp_autoc_entry);
}

static void				complete_missing_autocomplete(char *str_part,
	char *completion)
{
	int					i;
	char				*tmp;
	char				*res;

	i = 0;
	if (!completion)
		return ;
	if (!str_part || !(tmp = ft_strrchr(str_part, '/')))
		tmp = str_part;
	if (tmp && tmp[0] == '/')
		tmp++;
	while (completion[i])
		if (tmp && completion[i] == tmp[i])
			i++;
		else
			break ;
	tmp = ft_strdup(completion + i);
	res = escape_operator(tmp);
	insert_in_cli(res);
	free(tmp);
	free(res);
}

static void				ft_sh_autocomplete_routine(t_ft_sh *sh, char *str_part)
{
	unsigned int	save_cur;
	t_list			*tmp;

	collect_data(str_part);
	sh->autocomplete_padding = get_autocomplete_el_with(sh->autocomplete) + 7;
	setpos_autocomplete(sh);
	tmp = ft_lstlast(sh->autocomplete);
	if (!tmp || ((((t_ft_autoc_entry*)tmp->content))->y_pos) +
		((sh->prompt_size + sh->buf.cursor) / sh->x_size) + 2 >= sh->y_size)
	{
		ft_putchar('\n');
		exec_term_command(TC_MOVEUP);
		exec_term_command_p(TC_MOVENRIGHT, 0, (sh->prompt_size +
			cursor_new_origin(sh)) % sh->x_size);
		cancel_autocompletion(sh, 0);
		if (tmp)
			exec_term_command(TC_BELL);
		return ;
	}
	save_cur = sh->cursor;
	prepare_autocomplete(sh, sh->autocomplete, save_cur);
	display_autocomplete(sh, sh->autocomplete);
}

void					ft_sh_autocomplete(unsigned long touch)
{
	char			*str_part;
	char			*completion;
	t_ft_sh			*sh;

	sh = get_ft_shell();
	str_part = NULL;
	str_part = extract_autocomplete_search(sh);
	if (!sh->autocomplete && touch == T_TAB)
		ft_sh_autocomplete_routine(sh, str_part);
	else if (sh->autocomplete &&
		(touch == T_TAB || touch == T_LARR || touch == T_RARR))
		move_in_autocompletion(touch);
	if (touch == T_ENTER || (sh->autocomplete && !sh->autocomplete->next &&
		!sh->autocomplete->prev && (sh->autocomplete_cusor = sh->autocomplete)))
	{
		completion = ft_strdup(((t_ft_autoc_entry*)
			sh->autocomplete_cusor->content)->name);
		cancel_autocompletion(sh, 0);
		complete_missing_autocomplete(str_part, completion);
		free(completion);
	}
	free(str_part);
}
