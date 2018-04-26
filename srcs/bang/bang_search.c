/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:13:59 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/26 15:14:01 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char *get_history_at(int nb, int *j)
{
	const t_list	*list = get_ft_shell()->history;
	int	len = ft_lstsize((t_list*)list);
	t_list *ptr;

	char *iota;

	nb += nb < 0 ? len + 1 : 0;
	if (nb <= 0 || nb > len)
		return (NULL);
	iota = ft_itoa(nb);
	*j += ft_strlen(iota);
	ptr = (t_list*)list;
	while (len != nb && len > 0)
	{
		ptr = ptr->next;
		len--;
	}
	if (len != nb)
		ft_error(-9, iota);
	ft_strdel(&iota);
	return (len == nb ?
		ft_strdup(((t_ft_hist_entry*)(ptr->content))->command) : NULL);
}

char *cmp_history(char *str, int *j)
{
	char *tmp;
	char *ret;

	while (str[*j] && ft_isalpha(str[*j]))
		*j += 1;
	tmp = ft_strndup(str, *j + 1);
	ret = search_history_nav(get_ft_shell(), tmp, 1);
	if (!ret)
		ft_error(-9, tmp);
	ft_strdel(&tmp);
	return (ret ? ft_strdup(ret) : NULL);
}

void replace_bang(char **str, int *i, int *j, char *bang)
{
	char *ret;

	ret = ft_strnew(ft_strlen(*str) + ft_strlen(bang));
	ft_strncpy(ret, *str, *i);
	ft_strcat(ret, bang);
	ft_strcat(ret, *str + *i + *j + 1);
	ft_strdel(str);
	*str = ret;
}
