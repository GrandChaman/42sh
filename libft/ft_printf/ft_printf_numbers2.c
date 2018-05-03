/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:18:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/24 18:26:29 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdarg.h>
#include "ft_printf_format_list.h"
#include "libft.h"

void	print_binary(t_ptf_buf *buf, t_ptf_toprint format, t_ptf_param p)
{
	unsigned long long	n;
	int					len;
	char				*istr;

	if (format.len)
		ft_putnstr(buf, format.str, format.len);
	n = extract_nb(p, buf->ap);
	istr = ft_itoa_base(n, 2);
	len = ft_strlen(istr);
	p.padding -= ((p.hashtag && n) ? 2 : 0);
	if ((p.hashtag && n) && p.zero)
		ft_putnstr(buf, "0b", 2);
	handle_padding(buf, p, (n || p.precision ? len : -1), BEFORE);
	if ((p.hashtag && n) && !p.zero)
		ft_putnstr(buf, "0b", 2);
	(p.precision > 0 ? print_padding(buf, '0', p.precision - len) : 0);
	if (n || p.precision)
		ft_putnstr(buf, istr, len);
	handle_padding(buf, p, (n || p.precision ? len : -1), AFTER);
	free(istr);
}
