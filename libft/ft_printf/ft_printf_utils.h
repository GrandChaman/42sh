/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:55:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/01/25 15:37:49 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H
# include <stdarg.h>
# include "ft_printf_format_list.h"
# define BEFORE 0
# define AFTER 1
# define WCHAR_GEN 128
# define WCHAR_1 192
# define WCHAR_2 224
# define WCHAR_3 240
# define PADDING_BUF_SIZE 1024

int					ft_printf_routine(t_ptf_buf *buf, const char *format);
void				ft_putnstr(t_ptf_buf *buf, const char *str, int stop);
int					ft_strccmp(const char *lhs, const char *rhs);
int					ft_strnccmp(const char *lhs, const char *rhs, int max);
void				format_handler(t_ptf_buf *buf, t_ptf_toprint format,
	int *i);
void				print_padding(t_ptf_buf *buf, char c, int len);
void				ft_putll(t_ptf_buf *buf, unsigned long long n);
unsigned long long	extract_nb(t_ptf_param param, va_list ap);
int					ft_nblen(unsigned long long nb);
unsigned long long	extract_nb_signed(t_ptf_param *param, va_list ap);
void				ft_strtolower(char *str);
int					is_arguments(const char *str);
int					is_format_identifier(const char *str);
void				handle_padding(t_ptf_buf *buf, t_ptf_param param,
	int len, int att);
unsigned int		wchar_size(unsigned int t);
int					wchar_length(unsigned int c);
int					is_utf8(unsigned int c);
int					should_override_zero(char c);
int					ft_strwlen(wchar_t *str, int max);

#endif
