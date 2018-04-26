/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 20:24:12 by bluff             #+#    #+#             */
/*   Updated: 2018/04/23 18:19:09 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# define ANSI_COLOR_RED        "\x1b[31m"
# define ANSI_COLOR_GREEN      "\x1b[32m"
# define ANSI_COLOR_YELLOW     "\x1b[33m"
# define ANSI_COLOR_BLUE       "\x1b[34m"
# define ANSI_COLOR_MAGENTA    "\x1b[35m"
# define ANSI_COLOR_CYAN       "\x1b[36m"
# define ANSI_COLOR_B_RED      "\x1b[1;31m"
# define ANSI_COLOR_B_GREEN    "\x1b[1;32m"
# define ANSI_COLOR_B_YELLOW   "\x1b[1;33m"
# define ANSI_COLOR_B_BLUE     "\x1b[1;34m"
# define ANSI_COLOR_B_MAGENTA  "\x1b[1;35m"
# define ANSI_COLOR_B_CYAN     "\x1b[1;36m"
# define ANSI_COLOR_RESET      "\x1b[0m"
# define ANSI_DEL_LINE         "\r\x1b[K"
# define BUFF_SIZE 10
# define PRGRM_NAME "42sh"
# define LIBFT_OK 0
# define LIBFT_ERR 1

typedef struct			s_gnl
{
	char				buffer[BUFF_SIZE + 1];
	char				*current_line;
	int					cursor;
	int					fd;
	int					ll;
}						t_gnl;

int						get_next_line(int const fd, char **line);

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
	struct s_list		*prev;
}						t_list;

typedef struct			s_param
{
	char				*args;
	size_t				content_size;
}						t_param;

typedef struct			s_btree {
	struct s_btree		*parent;
	struct s_btree		*right;
	struct s_btree		*left;
	void				*item;
}						t_btree;

typedef struct			s_dbuf {
	char				*buf;
	unsigned short		cursor;
	unsigned long		len;
}						t_dbuf;

typedef struct			s_void
{
	struct s_void *next;
	struct s_void *previous;
}						t_void;

char					*ft_strrchr_2(const char *s, int c);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
char					*ft_strffjoin(char *s1, char *s2);
char					*ft_strfjoin(char *s1, char *s2);
char					*ft_strpush(char *str, size_t idx, char c,
							size_t *buff_sz);
char					**ft_split_whitespaces(char *str);
void					ft_lstappend(t_list **head, t_list *nw);
char					*ft_str3join(char const *s1, char const *s2,
							char const *s3);
void					ft_bzero(void *s, size_t n);
void					*ft_memset(void *dest, int ch, size_t count);
void					*ft_memcpy(void *dest, const void *src, size_t count);
void					*ft_memccpy(void *dest, const void *src, int c,
							size_t n);
void					*ft_memmove(void *dest, const void *src, size_t count);
void					*ft_memchr(const void *ptr, int ch, size_t count);
int						ft_memcmp(const void *lhs, const void *rhs,
							size_t count);
size_t					ft_strlen(const char *str);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strdup(const char *str);
char					*ft_strndup(char *str, size_t size);
char					*ft_strncpy(char *dest, const char *src, size_t count);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strncat(char *dest, const char *src, size_t count);
char					*ft_strchr(const char *str, int ch);
char					*ft_strrchr(const char *str, int ch);
char					*ft_strstr(const char *str, const char *substr);
int						ft_strcmp(const char *lhs, const char *rhs);
int						ft_strncmp(const char *lhs, const char *rhs,
							size_t count);
char					*ft_strnstr(const char *str, const char *substr,
							size_t count);
int						ft_atoi(const char *str);
int						ft_isdigit(int ch);
int						ft_isalpha(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
void					ft_putchar(char c);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(const char *s, int fd);
void					ft_putendl_fd(const char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr(const char *s);
void					ft_putnbr(int n);
void					ft_putendl(const char *s);
int						ft_strcommon(char *s1, char *s2);
char					**ft_strsplit(char const *s, char c);
char					**ft_strsplit_multi(const char *s, int (*c)(int));
char					*ft_strsub(char const *s, unsigned int start,
							size_t len);
char					*ft_itoa(int n);
char					*ft_strjoin(char const *s1, char const *s2);
void					ft_striter(char *s, void (*f)(char*));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
							char (*f)(unsigned int, char));
char					*ft_strtrim(char const *s);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst,
							void (*del)(void *, size_t));
void					ft_lstdel(t_list **alst, void(*del)(void*, size_t));
void					ft_lstadd(t_list **alst, t_list *nw);
void					ft_lstiter(t_list *lst, void(*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int						ft_any(char **tab, int (*f)(char*));
int						ft_count_if(char **tab, int (*f)(char*));
int						ft_find_next_prime(int nb);
void					ft_foreach(int *tab, int length, void (*f)(int));
int						ft_isprime(int nb);
int						ft_issort(int *tab, int length, int (*f)(int, int));
t_list					*ft_lstat(t_list *begin_list, int nbr);
t_list					*ft_lstfind(t_list *begin_list,
							void *data_ref, int (*cmp)());
void					ft_lstforeach_if(t_list *begin_list,
							void (*f)(void *), void *data_ref, int (*cmp)());
void					ft_lstforeach(t_list *begin_list, void (*f)(void *));
t_list					*ft_lstlast(t_list *begin_list);
void					ft_lstmerge(t_list **begin_list1, t_list *begin_list2);
void					ft_lstpush_back(t_list **begin_list,
							void *data, size_t size);
void					ft_lstpush_front(t_list **begin_list,
							void *data, size_t size);
void					ft_lstremove_if(t_list **begin_list,
							void *data_ref, int (*cmp)());
void					ft_lstreverse(t_list **begin_list);
int						ft_lstsize(t_list *begin_list);
void					ft_lstsort(t_list **begin_list, int (*cmp)());
int						*ft_map(int *tab, int length, int (*f)(int));
int						*ft_range(int min, int max);
int						ft_factorial(int nb);
int						ft_pow(int nb, int power);
int						ft_sqrt(int nb);
int						ft_islowercase(char *str);
int						ft_isuppercase(char *str);
char					*ft_strrev(char *str);
void					ft_swap(int *a, int *b);
void					ft_print_memory(const void *addr, size_t size);
int						ft_iswhitespace(int ch);
int						ft_atoi_base(const char *nb, const char *base);
t_btree					*ft_btree_create_node(void *item);
void					ft_btree_insert_data(t_btree **root, void *item,
							int (*cmpf)(void *, void *));
void					ft_btree_apply_infix(t_btree *root,
							void (*applyf)(void *));
void					ft_btree_apply_prefix(t_btree *root,
							void (*applyf)(void *));
void					ft_btree_apply_suffix(t_btree *root,
							void (*applyf)(void *));
void					ft_btree_destroy(t_btree **root);
int						ft_btree_count_node(t_btree *tree);
void					ft_perror(char *title, char *error);
char					*ft_itoa_base(unsigned long long nb, int base);
unsigned int			ft_numlen(unsigned int nb);
void					ft_free2d(void **arr);
char					**ft_str2ddup(char **arr);
int						ft_haschar(char *c, char ch);
int						ft_addparam(char *correct, char *chain, char param);
void					ft_free(void **tofree);
void					ft_lstdestroy(t_list **list);
int						dbuf_init(t_dbuf *buf);
int						dbuf_append(t_dbuf *buf, char *to_append);
int						dbuf_clear(t_dbuf *buf);
int						dbuf_destroy(t_dbuf *buf);
int						dbuf_insert(t_dbuf *buf, unsigned long pos,
							char to_insert);
int						dbuf_remove(t_dbuf *buf, unsigned long pos);
int						dbuf_substract(t_dbuf *buf);
int						dbuf_print(t_dbuf *buf, unsigned char fd);
int						ft_printf(const char *format, ...);
int						ft_fprintf(int fd, const char *format, ...);
int						ft_asprintf(char **ret, const char *format, ...);
int						ft_snprintf(char *ret, size_t size, const char *format,
							...);
int						ft_stralike(char *str1, char *str2, size_t len);
char					*ft_strjoin_multiple(int nb_args, ...);
char					*concate_array(char **arr);

#endif
