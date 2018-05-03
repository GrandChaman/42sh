/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete_local_file.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 16:40:02 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/17 16:43:47 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

static void		get_graphics_for_filetype(mode_t type, t_ft_autoc_entry *entry)
{
	entry->undeline = 0;
	if ((type & S_IFMT) == S_IFDIR)
		entry->color = ANSI_COLOR_B_RED;
	else if ((type & S_IFMT) == S_IFCHR)
		entry->color = ANSI_COLOR_CYAN;
	else if ((type & S_IFMT) == S_IFLNK)
	{
		entry->color = ANSI_COLOR_GREEN;
		entry->undeline = 1;
	}
	else
		entry->color = "";
}

static void		load_dir_autocomplete(DIR *dir, t_list **list, char *path,
	char *str_part)
{
	size_t				len;
	struct dirent		*dir_data;
	t_ft_autoc_entry	entry;
	struct stat			stat_buf;
	char				*fpath;

	len = 0;
	if (str_part)
		len = ft_strlen(str_part);
	while ((dir_data = readdir(dir)))
	{
		if (str_part && ft_stralike(dir_data->d_name, str_part, len))
			continue ;
		ft_asprintf(&fpath, "%s/%s", path, dir_data->d_name);
		if (!stat(fpath, &stat_buf))
			get_graphics_for_filetype(stat_buf.st_mode, &entry);
		free(fpath);
		entry.name = ft_strdup(dir_data->d_name);
		ft_lstpush_back(list, &entry, sizeof(t_ft_autoc_entry));
	}
}

static void		load_dir_and_add_slash_autocomplete(DIR *dir, t_list **list,
	char *path, char *str_part)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	load_dir_autocomplete(dir, list, path, str_part);
	if (sh->cursor > 0 && sh->buf.buf[sh->cursor - 1] != '/')
		insert_in_cli("/");
}

void			collect_data_local_file(t_list **list, char *str_part)
{
	DIR					*dir;
	char				*path;
	char				*slash;

	path = NULL;
	slash = NULL;
	if ((dir = opendir(str_part)))
		load_dir_and_add_slash_autocomplete(dir, list, str_part, NULL);
	else if (str_part && (slash = ft_strrchr(str_part, '/')))
	{
		path = ft_strndup2(str_part, (slash - str_part) + 1);
		if ((dir = opendir(path)))
			load_dir_autocomplete(dir, list, path, slash + 1);
		else
			ft_free((void**)&path);
	}
	if (!dir && !path)
	{
		path = getcwd(NULL, MAXPATHLEN);
		if ((dir = opendir(path)))
			load_dir_autocomplete(dir, list, path,
				(str_part && str_part[0] ? str_part : NULL));
	}
	(dir ? closedir(dir) : 0);
	free(path);
}
