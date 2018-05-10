/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:55:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/05/04 16:55:11 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "cli.h"

static int			hist_display(int lim)
{
	t_ft_sh			*sh;
	t_list			*tmp;
	t_ft_hist_entry	*entry;
	unsigned int	i;
	char			t_format[50];

	sh = get_ft_shell();
	i = 0;
	if (lim < 0 || lim >= sh->history_size)
		return (ft_fprintf(2, "42sh: history: %d: index out of range\n", lim));
	if (!(tmp = (lim ? ft_lstat(sh->history, sh->history_size - lim - 1)
		: ft_lstlast(sh->history))))
		return (0);
	if (lim)
		i = lim;
	while (tmp && ++i)
	{
		entry = (t_ft_hist_entry*)tmp->content;
		ft_bzero(t_format, 50);
		strftime(t_format, 50, "%d/%m/%G %H:%M:%S",
			localtime((const time_t *)&entry->timestamp));
		ft_printf("%d\t%s\t%s\n", i - 1, t_format, entry->command);
		tmp = tmp->prev;
	}
	return (0);
}

static int			hist_clear(void)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	ft_lstdel(&sh->history, delete_hist_entry);
	sh->history_size = 0;
	return (0);
}

static int			display_cmd(int argc, char **argv, int should_display,
	int argv_count)
{
	if (!should_display)
		return (0);
	while (argv_count < argc)
		ft_printf("%s\n", argv[argv_count++]);
	return (0);
}

static int			hist_del_at_offset(int off)
{
	t_ft_sh	*sh;
	t_list	*tmp;

	sh = get_ft_shell();
	if (sh->history_size >= SH_HIST_MAX_SIZE)
		off--;
	if (off < 0 || sh->history_size - off < 0)
		return (ft_fprintf(2, "42sh: history: %d: index out of range\n", off));
	if ((sh->history_size - off - 1) &&
		!(tmp = ft_lstat(sh->history, sh->history_size - off - 1)))
		return (1);
	ft_lstdelone((!(sh->history_size - off - 1) ? &sh->history : &tmp),
		delete_hist_entry);
	sh->history_size--;
	return (0);
}

int					bi_history(int argc, char **argv,
					char ***environ, t_ast_node *root)
{
	int			ret;
	t_hist_args	flgs;

	(void)environ;
	(void)root;
	if (!(ret = 0) && argc == 1)
		return (hist_display(0));
	else if (argc > 1 && ft_isdigit(argv[1][0]))
		return (hist_display(ft_atoi(argv[1])));
	args_init(&flgs);
	read_args(&flgs, argc, argv);
	if (flgs.err && ft_fprintf(2, "42sh: history: syntax error\n"))
		return (flgs.err);
	ret += (flgs.d ? hist_del_at_offset(flgs.d_val) : ret);
	ret += (flgs.p ? display_cmd(argc, argv, !flgs.s, flgs.argv_count) : ret);
	if (flgs.s)
		add_to_history(get_ft_shell(), flgs.concate_argv);
	ret += (flgs.awrn == 'a' ? hist_sync_file(argv[flgs.argv_count]) : ret);
	ret += (flgs.awrn == 'w' ? hist_write(argv[flgs.argv_count]) : ret);
	ret += (flgs.awrn == 'n' ? hist_sync(argv[flgs.argv_count]) : ret);
	ret += (flgs.awrn == 'r' ? hist_append_file(argv[flgs.argv_count]) : ret);
	ret += (flgs.c ? hist_clear() : ret);
	ft_strdel(&flgs.concate_argv);
	return (ret);
}
