/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:24:26 by fbertoia          #+#    #+#             */
/*   Updated: 2018/05/11 14:44:40 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

/*
**	A completer ulterieurement avec tous les specials parameters
*/

char	*special_parameters(char c)
{
	t_sh21      *sh21;
    const int   param = c - '0';

	sh21 = sh21_get();
	if (c == '?')
		return (ft_itoa(sh21->status));
	else if (c == '$')
		return (ft_itoa(getpid()));
    else if (ft_isdigit(c))
        return (param > sh21->argc ? NULL : ft_strdup(sh21->argv[param]));
	else if (c == '#')
		return (ft_itoa(sh21_get()->argc));
	else
		return (NULL);
}

char	*find_internal(char *str)
{
	int		i;
	char	*ret;
	char	c;

	i = skip_var(str);
	c = str[i];
	str[i] = 0;
	ret = ft_getenv(str, &sh21_get()->env.orig_env);
	if (!ret)
		ret = ft_getenv(str, &sh21_get()->env.local_var);
	str[i] = c;
	str += i;
	return (ret ? ft_strdup(ret) : ret);
}

char	*find_var(char *str)
{
	if (ft_strindex(SPECIAL_PARAMETERS, str[0]) >= 0)
		return (special_parameters(str[0]));
	else
		return (find_internal(str));
}
