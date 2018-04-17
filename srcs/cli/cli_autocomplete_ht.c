/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete_ht.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:29:28 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/17 13:19:51 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"
#include "sh21.h"

static char		*get_el_name(t_hash_bin *bin)
{
	if (!bin || !bin->path)
		return (NULL);
	return (ft_strrchr(bin->path, '/'));

}

static void		insert_ht_el_in_list(t_list **list,
	char *bin_name)
{
	t_ft_autoc_entry entry;

	entry.undeline = 0;
	entry.color = ANSI_COLOR_CYAN;
	entry.name = ft_strdup(bin_name);
	ft_lstpush_back(list, &entry, sizeof(t_ft_autoc_entry));
}

void			collect_data_ht(t_list **list, char *str_part)
{
	unsigned int		i;
	t_sh21				*lexer_s;
	char				*bin_name;
	t_hash_bin			*hash_el;
	size_t				len;

	lexer_s = sh21_get();
	if (!lexer_s || !str_part)
		return ;
	i = 0;
	len = ft_strlen(str_part);
	hash_el = &(lexer_s->env.hash_table[i]);
	while (i < HASH_SIZE)
	{
		if (!(bin_name = get_el_name(hash_el)))
		{
			i++;
			hash_el = &(lexer_s->env.hash_table[i]);
			continue ;
		}
		if (!ft_stralike(str_part, ++bin_name, len))
			insert_ht_el_in_list(list, bin_name);
		if ((hash_el = hash_el->next))
			continue ;
		i++;
	}
}
