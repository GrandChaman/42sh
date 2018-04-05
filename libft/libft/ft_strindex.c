/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertoia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:21:35 by fbertoia          #+#    #+#             */
/*   Updated: 2017/11/20 19:14:41 by fbertoia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** 							FT_STRINDEX
**
** Takes two arguments : the string and the decimal value of the character
** searched.
** Returns the index of the first character found into the string. Else, if
** if the character has not been found, the funcion returns (-1).
** In case a NULL string is sent in, (-1) is returned.
*/

int		ft_strindex(const char *str, int c)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	return (str[i] == c ? i : -1);
}
