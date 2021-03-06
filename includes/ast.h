/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:32:20 by hfontain          #+#    #+#             */
/*   Updated: 2018/05/11 14:38:20 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"
# include <stdlib.h>

# define SIZE_RANDOM_STR 10
# define TMP_HEREDOC_SIZE 64
# define TMP_PATH_RANDOM "/tmp/"
# define CONTENT_SIZE 1024
# define SPECIAL_PARAMETERS "@*#?-$!0123456789"
# define NB_ESCAPED_QUOTE 100

typedef struct			s_fd_cleanup
{
	struct s_fd_cleanup	*next;
	void				(*fd_function)(struct s_fd_cleanup*);
	int					fd_close;
	int					fd_reassign;
}						t_fd_cleanup;

typedef struct			s_assign_ls
{
	struct s_assign_ls	*next;
	char				*assignation;
}						t_assign_ls;

enum					e_pipe_side
{
	PIPE_IN = 0,
	PIPE_OUT = 1,
};

typedef struct			s_ast_node
{
	char				**argv;
	char				*content;
	char				*heredoc;
	char				*special_chars;
	int					esc_i[NB_ESCAPED_QUOTE];
	int					i;
	int					mod_gpid;
	int					nb_escaped_quote;
	int					pipe_fd[2];
	int					pipe_to_close;
	int					piped_cmd;
	int					quote_count;
	int					tag_gpid;
	int					tmp_fd_read;
	int					tmp_fd_write;
	int					need_to_fork;
	struct s_ast_node	*condition_node;
	struct s_ast_node	*left;
	struct s_ast_node	*redir_node;
	struct s_ast_node	*right;
	t_assign_ls			*assign_node;
	t_token_type		type;
}						t_ast_node;

typedef struct			s_args
{
	struct s_args		*next;
	char				*content;
}						t_args;

typedef struct			s_ast
{
	t_ast_node			*root_node;
	t_fd_cleanup		*fd_cleanup;
}						t_ast;

typedef void			(*t_fd_function)(t_fd_cleanup*);
typedef int				(*t_apply_fn)(t_ast_node*);
typedef int				(*t_exec_tree)(t_ast_node *root);

enum					e_fd
{
	in_fd,
	in_fd2,
	out_fd,
	tmp_fd,
	tmp_fd2,
};

int						ast_apply_prefix(t_ast_node *root);
int						ast_is_shell_cmd(t_token_type type);
int						ast_redir_node(t_token_type type);
int						exec_tree(t_ast_node *first);
int						func_amper(t_ast_node *root);
int						func_and_if(t_ast_node *root);
int						func_andgreat(t_ast_node *root);
int						func_assignment_word(t_ast_node *root);
int						assign_var(t_ast_node *node);
int						func_backslash(t_ast_node *root);
int						func_bang(t_ast_node *root);
int						func_case(t_ast_node *root);
int						func_clobber(t_ast_node *root);
int						func_dgreat(t_ast_node *root);
int						func_dless(t_ast_node *root);
int						func_dlessdash(t_ast_node *root);
int						func_do(t_ast_node *root);
int						func_dollar(t_ast_node *root);
int						func_done(t_ast_node *root);
int						func_dquote(t_ast_node *root);
int						func_dsemi(t_ast_node *root);
int						func_elif(t_ast_node *root);
int						func_else(t_ast_node *root);
int						func_endl(t_ast_node *root);
int						func_eoi(t_ast_node *root);
int						func_equal(t_ast_node *root);
int						func_esac(t_ast_node *root);
int						func_fi(t_ast_node *root);
int						func_for(t_ast_node *root);
int						func_function(t_ast_node *root);
int						func_greatand(t_ast_node *root);
int						func_greatanddash(t_ast_node *root);
int						func_greater(t_ast_node *root);
int						func_if(t_ast_node *root);
int						func_in(t_ast_node *root);
int						func_io_number(t_ast_node *root);
int						func_lbrace(t_ast_node *root);
int						func_less(t_ast_node *root);
int						func_lessand(t_ast_node *root);
int						func_lessanddash(t_ast_node *root);
int						func_lessgreat(t_ast_node *root);
int						func_lparen(t_ast_node *root);
int						func_magicq(t_ast_node *root);
int						func_name(t_ast_node *root);
int						func_newline(t_ast_node *root);
int						func_or_if(t_ast_node *root);
int						func_pipe(t_ast_node *root);
int						func_quote(t_ast_node *root);
int						func_rbrace(t_ast_node *root);
int						func_redirection(t_ast_node *root);
int						func_rparen(t_ast_node *root);
int						func_select(t_ast_node *root);
int						func_semi(t_ast_node *root);
int						func_space(t_ast_node *root);
int						func_tab(t_ast_node *root);
int						func_then(t_ast_node *root);
int						func_time(t_ast_node *root);
int						func_until(t_ast_node *root);
int						func_while(t_ast_node *root);
int						func_word(t_ast_node *root);
int						redir_token(t_token_type type);
int						shell42_exec(char *str);
t_ast_node				*ast_create_leaf(t_token_type type, t_lex **elem);
t_ast_node				*ast_create_node(t_token_type type, char *str);
t_ast_node				*ast_create_op(t_ast_node *node, t_lex **lex);
t_ast_node				*ast_create_tree(t_lex *lex);
t_ast_node				*redir_node(t_lex **lex, t_ast_node *node);
t_fd_cleanup			*create_fd_cleanup(t_fd_function fd_function,
							int fd_close, int fd_reassign);
void					ast_free_node(t_ast_node *node);
void					ast_free_one_node(t_ast_node *node);
void					fd_close(t_fd_cleanup *elem);
void					fd_reassign(t_fd_cleanup *elem);
void					heredoc_node(t_ast_node *node);

int						is_compound_token(t_token_type type);
t_ast_node				*ast_assignment_word(t_lex **lex, t_ast_node *node);
t_ast_node				*ast_pipe(t_lex **lex, t_ast_node *root);
t_ast_node				*ast_while(t_lex **lex, t_ast_node *root);
t_ast_node				*ast_until(t_lex **lex, t_ast_node *root);
t_ast_node				*ast_word(t_lex **lex, t_ast_node *node);
t_ast_node				*ast_compound_list(t_lex **lex, t_ast_node *node);
t_ast_node				*ast_else(t_lex **lex, t_ast_node *root);
t_ast_node				*ast_elif(t_lex **lex, t_ast_node *root);
t_ast_node				*ast_if(t_lex **lex, t_ast_node *node);
t_ast_node				*ast_bang(t_lex **lex, t_ast_node *node);
t_ast_node				*ast_pipeline(t_lex **lex, t_ast_node *node);
void					ast_redir_pipe(t_lex **lex, t_ast_node *node);

char					*format_word(char **str, t_ast_node *node);
char					*word(char **argv);
char					*add_str(char **ret, char **ptr, int *i);
char					*find_var(char *str);
int						skip_var(char *str);
void					case_backslash(char **ret, char **ptr,
							int *i, t_ast_node *node);
void					case_dollar(char **ret, char **ptr, int *i);
void					case_quote(char **ret, char **ptr, int *i);
void					case_dquote(char **ret, char **ptr, int *i,
							t_ast_node *node);
void					case_tilde(char **ret, char **ptr, int *i);
int						escaped_char(char *argv, t_ast_node *node, int *i,
							int *j);
void					case_quote_args(char *argv, int *i, int *j,
							t_ast_node *node);
t_args					*new_args(char *argv, int *j, int *i);
void					case_space(char *argv, int *i[2], t_ast_node *node,
							t_args **list);
char					**split_args(char *argv, t_ast_node *node);
char					**copy_list_to_array(t_args **list);
void					del_el(void **el);
void					ast_print(t_ast_node *root);
void					set_job(t_ast_node *root);
void					reset_job(t_ast_node *root);
static t_exec_tree		g_exec_fn[] =
{
	NULL,
	func_word,
	func_assignment_word,
	func_name,
	func_newline,
	func_io_number,
	func_and_if,
	func_or_if,
	func_dsemi,
	func_redirection,
	func_redirection,
	func_redirection,
	func_redirection,
	func_redirection,
	func_redirection,
	func_redirection,
	func_redirection,
	func_redirection,
	func_redirection,
	func_redirection,
	func_equal,
	func_if,
	func_then,
	func_else,
	func_elif,
	func_fi,
	func_do,
	func_done,
	func_case,
	func_esac,
	func_while,
	func_until,
	func_function,
	func_select,
	func_for,
	func_lbrace,
	func_rbrace,
	func_bang,
	func_in,
	func_eoi,
	func_pipe,
	func_amper,
	func_semi,
	func_redirection,
	func_redirection,
	func_lparen,
	func_rparen,
	func_dollar,
	func_magicq,
	func_backslash,
	func_dquote,
	func_quote,
	func_space,
	func_tab,
	func_endl,
	NULL,
	NULL
};

#endif
