/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_list.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:25:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/15 16:11:04 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FORMAT_LIST_H
# define FT_PRINTF_FORMAT_LIST_H
# define FLAG_LIST "-+ #0123456789.hljzcsoudixpXDIUOCS%*"
# define DONT_OVERZERO "cs%"
# define LR 0
# define UP 1
# define PTR 2
# include <stdlib.h>
# include "libft.h"

enum							e_length_modifier {NONE, HH, H, LL, L, J, Z};

typedef struct					s_length_modifier
{
	const char					*trigger;
	enum e_length_modifier		code;

}								t_length_modifier;

typedef struct					s_color_code
{
	const char					*trigger;
	const char					*code;

}								t_color_code;

typedef struct					s_ptf_buf
{
	t_dbuf						buf;
	va_list						ap;
}								t_ptf_buf;

typedef struct					s_ptf_param
{
	int							hashtag;
	int							zero;
	int							minus;
	int							plus;
	int							space;
	int							padding;
	int							precision;
	int							neg;
	enum e_length_modifier		lm;

}								t_ptf_param;

typedef struct					s_ptf_toprint
{
	const char					*str;
	const char					*format;
	int							start;
	int							len;

}								t_ptf_toprint;

typedef struct					s_ptf_format
{
	const char					*trigger;
	void						(*f)(t_ptf_buf *buf, t_ptf_toprint format,
		t_ptf_param param);

}								t_ptf_format;

typedef void					(*t_ft_printf_param)(const char *c,
	t_ptf_param *p, int *i, va_list ap);

void							parse_flags(const char *c, t_ptf_param *p,
	int *i, va_list ap);
void							parse_length_modifier(const char *c,
	t_ptf_param *p, int *i, va_list ap);
void							parse_numbers(const char *c, t_ptf_param *p,
	int *i, va_list ap);
int								skip_to_format(const char *str);
void							init_param(t_ptf_param *param);
t_ptf_toprint					get_toprint(const char *format, int start,
	int stop);

static t_ft_printf_param		g_param_list[] = {
	parse_flags,
	NULL,
	NULL,
	parse_flags,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	parse_numbers,
	parse_flags,
	NULL,
	parse_flags,
	parse_numbers,
	NULL,
	parse_flags,
	parse_numbers,
	parse_numbers,
	parse_numbers,
	parse_numbers,
	parse_numbers,
	parse_numbers,
	parse_numbers,
	parse_numbers,
	parse_numbers,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	parse_length_modifier,
	NULL,
	parse_length_modifier,
	NULL,
	parse_length_modifier,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	parse_length_modifier
};

void							hex_handler(int mode, t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param p);

void							print_string(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_char(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_pourcent(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_octal(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_unsigned(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_signed(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_hex(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_hex_upper(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_unsigned_upper(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_signed_upper(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_wchar(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_wstring(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_octal_upper(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_pointer(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param param);
void							print_binary(t_ptf_buf *buf,
	t_ptf_toprint format, t_ptf_param p);

static const t_ptf_format g_format_list[] = {
	{"c", print_char},
	{"s", print_string},
	{"o", print_octal},
	{"u", print_unsigned},
	{"d", print_signed},
	{"i", print_signed},
	{"x", print_hex},
	{"p", print_pointer},
	{"b", print_binary},
	{"X", print_hex_upper},
	{"D", print_signed_upper},
	{"I", print_signed_upper},
	{"U", print_unsigned_upper},
	{"O", print_octal_upper},
	{"C", print_wchar},
	{"S", print_wstring},
	{"%", print_pourcent},
	{NULL, NULL}
};

static const t_color_code g_color_list[] = {
	{"red", ANSI_COLOR_RED},
	{"green", ANSI_COLOR_GREEN},
	{"yellow", ANSI_COLOR_YELLOW},
	{"blue", ANSI_COLOR_BLUE},
	{"magenta", ANSI_COLOR_MAGENTA},
	{"cyan", ANSI_COLOR_CYAN},
	{"bred", ANSI_COLOR_B_RED},
	{"bgreen", ANSI_COLOR_B_GREEN},
	{"byellow", ANSI_COLOR_B_YELLOW},
	{"bblue", ANSI_COLOR_B_BLUE},
	{"bmagenta", ANSI_COLOR_B_MAGENTA},
	{"bcyan", ANSI_COLOR_B_CYAN},
	{"del", ANSI_DEL_LINE},
	{"eoc", ANSI_COLOR_RESET},
	{NULL, 0}
};

#endif
