/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:21:13 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/17 11:11:21 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "sh21.h"

static t_hash_bin	*add_paths(char *bin_name, char *path_dir, t_env *env)
{
	unsigned int	index;
	char			tmp[OPEN_MAX];
	t_hash_bin		*ptr;

	ft_strlcpy(tmp, path_dir, OPEN_MAX);
	ft_strlcat(tmp, "/", OPEN_MAX);
	ft_strlcat(tmp, bin_name, OPEN_MAX);
	index = ft_hash(bin_name) % (HASH_SIZE);
	ptr = &env->hash_table[index];
	if (ptr->path)
	{
		while (ptr->path && ptr->next)
			ptr = ptr->next;
		ptr->next = (t_hash_bin*)malloc(sizeof(t_hash_bin));
		if (!(ptr = ptr->next))
			ft_exit(errno, "malloc");
		ptr->next = NULL;
	}
	ptr->path = ft_strdup(tmp);
	return (ptr);
}

static void			search_paths(char *path_dir, t_env *env)
{
	DIR				*dirp;
	struct dirent	*file;

	if (!(dirp = opendir(path_dir)))
		return ;
	while ((file = readdir(dirp)))
	{
		if (file->d_name[0] != '.')
			add_paths(file->d_name, path_dir, env);
	}
	if (closedir(dirp) < 0)
		ft_error(errno, "closedir");
}

int					find_bin_paths(t_env *env, char ***environ)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_getenv("PATH", environ);
	if (!tmp)
	{
		ft_error(-2, "hash");
		return (1);
	}
	del_hash(env);
	paths = ft_strsplit(tmp, ':');
	while (paths[++i])
		search_paths(paths[i], env);
	del_arr(&paths);
	return (0);
}
