/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:53:33 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 15:58:19 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <wchar.h>
# include "libft.h"

# define MODIFIER "hljz"
# define FLAGS "#0- +.*"
# define FLAGSNUM "#0- +.*123456789"
# define NUM "0123456789"

/*
** Colors to use for printf
*/

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define UNDERLIGN "\x1b[4m"
# define BOLD "\x1b[1m"
# define HIDDEN "\x1b[8m"
# define NOCOLOR "\033[0m"

/*
** Management of the buffer
*/

# ifndef BUFF_SIZE_P
#  define BUFF_SIZE_P 20000
# endif
# ifndef BUFF_SIZE_ERROR_P
#  define BUFF_SIZE_ERROR_P 500
# endif
# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif

enum	e_flags
{
	hashtag,
	zero,
	minus,
	space,
	plus,
	dot,
	star,
	modulo
};

enum	e_modifiers
{
	hash,
	hashash,
	ell,
	ellell,
	jay,
	zed
};

typedef struct		s_p
{
	int				flags;
	int				width;
	int				precision;
	int				modifier;
	char			converter;
	int				delta;
	int				err;
	int				error;
	int				mbcur;
	int				ret;
	int				toskip;
	int				i;
	wint_t			c;
	int				intermed_c;
	int				tmp;
	int				phold;
	int				third;
	int				fd;
	int				buff_size;
	int				vsprintf;
	int				asprintf;
}					t_p;

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_asprintf(char **ret, const char *format, ...);
int					ft_vsprintf(char *str, const char *format, ...);
void				var_reader(char *format, char **str, va_list ap, t_p *box);
int					reader(char *format, char **str, va_list ap, t_p *box);
int					ptr_color(char *format, char **str, t_p *box, va_list ap);
void				ft_copy_colors(char **str, char *color_type, t_p *box);
void				box_initializer(t_p *box);
int					ft_flags(char **format, t_p *box, va_list ap, int stri);
int					ft_modifiers(char **format, t_p *box);
void				ft_buffalloc(char **ptr, t_p *box, int type);
int					ptr_s(char **str, va_list ap, t_p *box);
int					ptr_smaj(char **str, va_list ap, t_p *box);
int					ptr_c(char **str, va_list ap, t_p *box);
int					ptr_cmaj(char **str, va_list ap, t_p *box);
int					ptr_p(char **str, va_list ap, t_p *box);
int					ptr_pct(char **str, va_list ap, t_p *box);
int					ptr_d(char **str, va_list ap, t_p *box);
int					ptr_u(char **str, va_list ap, t_p *box);
int					ptr_o(char **str, va_list ap, t_p *box);
int					ptr_x(char **str, va_list ap, t_p *box);
int					ptr_lambda(char *format, char **str, t_p *box);
int					ptr_b(char **str, va_list ap, t_p *box);
void				ptr_c_case(char **str, char c, t_p *box);
void				ft_insert_spaces(char **str, t_p *box);
void				ptr_cmaj_case(char **str, t_p *box);
void				ptr_copy(char **str, char *tab_, t_p *box);
int					error_case(t_p *box);
void				ptr_s_null_case(char **str, t_p *box);

char				*ft_lltoa(long long n, t_p *box);
void				ft_sub_lltoa(long long n, int *i, char **ret);
long long			ft_get_number(va_list ap, t_p *box);

void				ft_xtoa_insert_spaces(char **str, t_p *box);
unsigned long long	ft_boux_get_number(va_list ap, t_p *box);
char				*ft_bouxtoa_base(unsigned long long value, t_p *box);
void				ft_sub_bouxtoa_base(unsigned long long value,
					t_p *box, int *i, char **ret);
void				ft_hashtag_box(char **str, t_p *box, unsigned long long x);
void				ft_bxtoa_insert_flags(char **str,
					t_p *box, int len, unsigned long long x);
void				ft_flag_reorganize(t_p *box);
void				ft_unsigned_insert_spaces(char **str, t_p *box);

#endif
