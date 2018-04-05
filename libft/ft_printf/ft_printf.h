/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:39:32 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/25 15:52:50 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>

int		ft_printf(const char *format, ...);
int		ft_fprintf(int fd, const char *format, ...);
int		ft_asprintf(char **ret, const char *format, ...);
int		ft_snprintf(char *ret, size_t size, const char *format, ...);

#endif
