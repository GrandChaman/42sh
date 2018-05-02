/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:55:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/05/02 22:23:16 by fle-roy          ###   ########.fr       */
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
	if (!(tmp = (lim ? ft_lstat(sh->history, lim) : ft_lstlast(sh->history))))
		return (0);
	if (lim)
		i = sh->history_size - lim;
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
	t_hist_args	flags;

	(void)environ;
	(void)root;
	if (!(ret = 0) && argc == 1)
		return (hist_display(0));
	args_init(&flags);
	read_args(&flags, argc, argv);
	if (flags.err)
		return (flags.err);
	ret = (flags.d ? hist_del_at_offset(flags.d_val) : ret);
	ret = (flags.p ? display_cmd(argc, argv, !flags.s, flags.argv_count) : ret);
	if (flags.s)
		add_to_history(get_ft_shell(), flags.concate_argv);
	if (flags.awrn == 'a')
		ret = hist_sync_file(argv[flags.argv_count]);
	else if (flags.awrn == 'w')
		ret = hist_write(argv[flags.argv_count]);
	else if (flags.awrn == 'n')
		ret = hist_sync(argv[flags.argv_count]);
	ret = (flags.c ? hist_clear() : ret);
	ret = (flags.awrn == 'r' ? hist_append_file(argv[flags.argv_count]) : ret);
	ft_strdel(&flags.concate_argv);
	return (ret);
}
