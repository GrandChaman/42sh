/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_expr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 21:36:44 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/24 21:36:47 by rfautier         ###   ########.fr       */
=======
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:52:58 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/24 16:22:21 by hfontain         ###   ########.fr       */
>>>>>>> 2b1149ee5bc8f333757165fb0124ab7727587864
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int		is_number(char *str, int *i)
{
	int		nbr;

	nbr = 0;
	while (ft_isalnum(str[*i]))
	{
		if (!ft_isdigit(str[*i]))
			*i = *i + 1;
		else
		{
			nbr = nbr * 10 + (str[*i] - '0');
			*i = *i + 1;
		}
	}
	return (nbr);
}

static int		check_parenthese(char *str, int *i)
{
	int		nbr;

	while (str[*i] == ' ' || str[*i] == '\n')
		*i = *i + 1;
	if (str[*i] == '(')
	{
		*i = *i + 1;
		nbr = main_expr(str, i);
		if (str[*i] == ')')
			*i = *i + 1;
		return (nbr);
	}
	return (is_number(str, i));
}

static int		is_factors(char *str, int *i)
{
	int		nbr;
	int		nbr2;
	char	op;

	nbr = check_parenthese(str, i);
	while (str[*i])
	{
		while (str[*i] == ' ' || str[*i] == '\n')
			*i = *i + 1;
		op = str[*i];
		if (op != '/' && op != '*' && op != '%')
			return (nbr);
		*i = *i + 1;
		nbr2 = check_parenthese(str, i);
		if (op == '/')
			nbr = nbr / nbr2;
		else if (op == '*')
			nbr = nbr * nbr2;
		else
			nbr = nbr % nbr2;
	}
	return (nbr);
}

<<<<<<< HEAD
int				main_expr(char *str)
=======
int				main_expr(char *str, int *i)
>>>>>>> 2b1149ee5bc8f333757165fb0124ab7727587864
{
	int		nbr;
	int		nbr2;
	char	op;
	int		i;

	i = 0;
	nbr = is_factors(str, &i);
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\n')
			i = i + 1;
		op = str[i];
		if (op != '+' && op != '-')
			return (nbr);
		i = i + 1;
		nbr2 = is_factors(str, &i);
		if (op == '+')
			nbr = nbr + nbr2;
		else
			nbr = nbr - nbr2;
	}
	return (nbr);
}

int				ft_eval_expr(char *ori, int *end)
{
	int		i;
	int		o;
	char	*str;
	char	*lol;

	i = -1;
	o = 0;
	str = NULL;
	while (ori[++i])
	{
		if (o == 0 && i != 0)
			break ;
		if (ori[i] == '(')
			o++;
		if (ori[i] == ')')
			o--;
	}
	*end = i;
	lol = ft_strdup(ori);
	str = ft_strsub(lol, 0, i);
<<<<<<< HEAD
	str = find_var_expr(str);
	i = main_expr(str);
=======
	i = 0;
	i = main_expr(str, &i);
>>>>>>> 2b1149ee5bc8f333757165fb0124ab7727587864
	free(str);
	free(lol);
	return (i);
}
