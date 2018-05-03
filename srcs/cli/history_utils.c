/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:44:15 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/19 17:21:10 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"
#include "sh21.h"

void				delete_hist_entry(void *entry, size_t size)
{
	t_ft_hist_entry *hentry;

	(void)size;
	hentry = (t_ft_hist_entry*)entry;
	free(hentry->command);
	free(hentry);
}

void				trim_history(t_ft_sh *sh)
{
	int		i;
	t_list	*lcpy;

	i = 0;
	lcpy = sh->history;
	while (i++ < SH_HIST_MAX_SIZE && lcpy)
		lcpy = lcpy->next;
	if (lcpy)
	{
		ft_lstdel(&lcpy, delete_hist_entry);
		sh->history_size = SH_HIST_MAX_SIZE;
	}
}

void				parse_and_add_to_history(t_ft_sh *sh, char *line)
{
	char			*tmp;
	t_ft_hist_entry	entry;

	tmp = ft_strchr(line, ' ');
	if (tmp)
		entry.command = ft_strdup(tmp + 1);
	else
		entry.command = ft_strdup(line);
	entry.timestamp = ft_atoi(line);
	ft_lstpush_front(&sh->history, &entry, sizeof(entry));
	sh->history_size++;
	if (sh->history_size > SH_HIST_MAX_SIZE)
		trim_history(sh);
}

char				*get_history_file(void)
{
	char	*home;
	char	*path;
	t_sh21	*lexer_s;

	lexer_s = sh21_get();
	if (!lexer_s)
		return (NULL);
	home = ft_getenv("HOME", &lexer_s->env.orig_env);
	ft_asprintf(&path, "%s/.42sh_history", home);
	return (path);
}
