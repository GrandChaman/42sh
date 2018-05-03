/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:15:51 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 16:26:10 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static const unsigned long		g_prime_table[42] =
{
	0x0049, 0x0059, 0x004f, 0x0053, 0x0061, 0x0067, 0x0065,
	0x006b, 0x006d, 0x001f, 0x0025, 0x0029, 0x002b, 0x002f,
	0x0035, 0x003b, 0x003d, 0x0043, 0x0047, 0x0071, 0x0089,
	0x008b, 0x007f, 0x0083, 0x0095, 0x0097, 0x009d, 0x00ad,
	0x00a3, 0x00a7, 0x00b3, 0x00b5, 0x025f, 0x0265, 0x0269,
	0x026b, 0x0277, 0x0281, 0x0283, 0x0287, 0x028d, 0x0293
};

unsigned long long	ft_hash(const char *str)
{
	unsigned long long		hold;
	const unsigned char		*ustr = (const unsigned char *)str;

	hold = 0;
	while (*ustr)
	{
		hold = (hold * (g_prime_table[*ustr % 42])) + *ustr;
		++ustr;
	}
	return (hold);
}
