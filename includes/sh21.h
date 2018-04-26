/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:38:34 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/26 14:19:36 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include "cli.h"
# include "libft.h"
# include "ft_printf.h"
# include "error_message.h"
# include "lexer.h"
# include "ast.h"
# include "env.h"
# include "builtins.h"
# include "job_control.h"

# define BUFF_SIZE_INPUT_21SH 1024

typedef struct		s_term
{
	char			*term_name;
	struct termios	term;
	int				isatty;
	int				fd_script_shell;
}					t_term;

typedef struct		s_sh21
{
	t_term			terminal;
	t_lex			*lex;
	t_ast			tree;
	t_env			env;
	char			*buf;
	int				signal;
	int				debug_tty;
	t_list			*envl;
	int				ret;
	int				script;
	int				status;
}					t_sh21;

static int			g_shell_idx = 0;

int					correct_form_eval_expr(char *str);
char				*return_prompt(int stock);
char				*bracket(char *cmd, int i);
char				*find_var_expr(char *str);
int					ft_eval_expr(char *str, int *end, int o);
int					main_expr(char *str, int *i);
int					bang(char **str);
char				*random_str(size_t len);
void				del_flist(void **lst);
char				**sh21_envchar(t_sh21 *sh21);
int					all_signal(void);

int					ft_error(int err, const char *s);
int					input_piped_script(t_sh21 *sh21, char **argv);
int					parser(t_lex *lex);
int					sh21_addenv(t_sh21 *sh21, const char *n, const char *v);
int					sh21_exec(char **av, char ***env, t_ast_node *root);
int					sh21_loadenv(t_sh21 *sh21, char **environ);
t_sh21				*sh21_get(void);
t_sh21				*sh21_init(char *env[]);
void				del_ast(t_ast_node **node);
void				del_hash(t_env	*env);
void				del_lex(void **lex);
void				del_redir(void **node);
void				del_sh21(void);
void				del_sh21_exit(void);
void				ft_exit(int err, const char *s);
void				handle_windowsize(int nb);
void				init_term(t_sh21 *sh21);
void				reinit_term(t_sh21 *sh21);
void				set_debugtty(void);
void				ft_lstpush(t_list *lst, t_list *lnew);
void				ft_lstqueue(t_list **lst, t_list *lnew);
size_t				compute(const char *n, const char *v, \
					char **str, void *to_free);
char				*remove_char(char *str);

int 	change_fd(t_ast_node *root);
int 	reset_fd(t_ast_node *root);

#endif
