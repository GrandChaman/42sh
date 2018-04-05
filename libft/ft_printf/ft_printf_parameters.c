/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parameters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:46:22 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/25 13:56:23 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "libft.h"
#include "ft_printf_extract_dynamic_param.h"
#include <stdarg.h>

void			init_param(t_ptf_param *param)
{
	param->hashtag = 0;
	param->zero = 0;
	param->minus = 0;
	param->plus = 0;
	param->space = 0;
	param->padding = -1;
	param->precision = -1;
	param->neg = 0;
	param->lm = NONE;
}

int				skip_to_format(const char *str)
{
	int i;
	int ii;

	i = 0;
	while (str[i] && is_arguments(str + i))
	{
		ii = -1;
		while (g_format_list[++ii].trigger)
			if (ft_strccmp(g_format_list[ii].trigger, &str[i]))
				return (i);
		i++;
	}
	return (i);
}

void			parse_length_modifier(const char *c, t_ptf_param *p,
	int *i, va_list ap)
{
	int tmp;

	(void)ap;
	tmp = 0;
	if ((tmp = ft_strccmp(c, "hh")) == 2)
		p->lm = HH;
	else if ((tmp = ft_strccmp(c, "ll")) == 2)
		p->lm = LL;
	else if ((tmp = ft_strccmp(c, "h")))
		p->lm = H;
	else if ((tmp = ft_strccmp(c, "l")))
		p->lm = L;
	else if ((tmp = ft_strccmp(c, "j")))
		p->lm = J;
	else if ((tmp = ft_strccmp(c, "z")))
		p->lm = Z;
	*i += tmp;
}

void			parse_flags(const char *c, t_ptf_param *p,
	int *i, va_list ap)
{
	(void)ap;
	if (*c == '#')
		p->hashtag = 1;
	else if (*c == ' ')
		p->space = 1;
	else if (*c == '-')
	{
		p->minus = 1;
		p->zero = 0;
	}
	else if (*c == '+')
		p->plus = 1;
	else if (*c == '0' && !p->zero && p->precision < 0)
		p->zero = 1;
	if (p->plus)
		p->space = 0;
	(*i)++;
}

void			parse_numbers(const char *c, t_ptf_param *p,
	int *i, va_list ap)
{
	int len;

	len = 0;
	if (ft_isdigit(*c))
	{
		p->padding = ft_atoi(c);
		len = ft_nblen(p->padding);
	}
	else if (*c == '.')
	{
		p->zero = 0;
		if (*(c + 1) == '*')
			p->precision = extract_dyn_param(NULL, ap);
		else if (ft_isdigit(*(c + 1)))
			p->precision = ft_atoi(c + 1);
		else
			p->precision = 0;
		len = ft_nblen(p->precision) + 1;
	}
	else if (*c == '*')
	{
		p->padding = extract_dyn_param(&(p->minus), ap);
		len = 1;
	}
	*i += len;
}
