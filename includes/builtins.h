/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:54:39 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/19 17:12:33 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "sh21.h"

# define AF			1 << 0
# define WF			1 << 1
# define RF			1 << 2
# define NF			1 << 3
# define D_ERR		1 << 4
# define AWRN_ERR	1 << 5
# define INVARG		1 << 6
//
// typedef struct			s_hist_args
// {
// 	int		c;
// 	int		d;
// 	int		d_val;
// 	int		p;
// 	int		s;
// 	int		awrn;
// 	int		err;
// }						t_hist_args;

typedef struct			s_flag
{
	int					flag_p;
	int					flag_l;
	int					idx;
	int					buf_to_free;
}						t_flag;

typedef struct	s_hist_args
{
	int		c;
	int		d;
	int		d_val;
	int		p;
	int		s;
	int		awrn;
	int		err;
	int		argv_count;
}				t_hist_args;

void					args_init(t_hist_args *args);
char					*cd_rules5_2(char *curpath);
int						go_home(char ***environ);
int						ft_echo(char *argv[]);
int						find_bin_paths(t_env *env, char ***environ);

char					*ft_getenv(const char *name, char ***environ);
int						ft_unsetenv(const char *name, char ***environ);
int						ft_putenv(const char *str, char ***environ);
int						ft_setenv(const char *name, const char *value,
						int override, char ***environ);
int						print_env(char **env);
int						env_usage(char c, int option);
void print_hhh(t_hist_args flags);
int		print_one_jobs(int tague);
int					check_jobs(int tague);
int					get_last_last_jobs(void);
int					get_last_jobs(void);
int					bi_kill(int argc, char **argv, char ***environ, t_ast_node *root);
int					bi_fg(int argc, char **argv, char ***environ, t_ast_node *root);
int					bi_bg(int argc, char **argv, char ***environ, t_ast_node *root);
int					bi_jobs(int argc, char **argv, char ***environ, t_ast_node *root);
int						bi_cd(int argc, char **argv, char ***environ, t_ast_node *root);
int						bi_echo(int argc, char **argv, char ***environ, t_ast_node *root);
int						bi_env(int argc, char **argv, char ***environ, t_ast_node *root);
int						bi_exit(int argc, char **argv, char ***environ, t_ast_node *root);
int						bi_setenv(int argc, char **argv, char ***environ, t_ast_node *root);
int						bi_unsetenv(int argc, char **argv, char ***environ, t_ast_node *root);
int						bi_hash(int argc, char **argv, char ***environ, t_ast_node *root);
int						bi_export(int argc, char **argv, char ***environ, t_ast_node *root);
int						bi_unset(int argc, char **argv, char ***environ, t_ast_node *root);
int						bi_history(int argc, char **argv, char ***environ, t_ast_node *root);
int						hist_write(char *path);
int						hist_append_file(char *path);
int						hist_sync(char *path);
int						hist_sync_file(char *path);
int						hist_divergence(char *path, char **line,
	t_list **hist, int *fd);

void					read_args(t_hist_args *args, int argc, char **argv);

char					*cd_rule5(char *curpath, char ***environ);
int						cd_rule8_casedotdot(int *i, char *curpath,
							int free_curpath);
int						cd_rule8(char *curpath, char ***environ, int flag,
							int free_curpath);
int						cd_rule7(char *curpath, char ***environ, int flag,
							int free_curpath);
int						cd_rule_dash(char ***environ, int flag);
int						change_oldpwd_pwd(char ***environ, const char *path);
int						go_home(char ***environ);
int						ft_is_dir(char *buf, int print);
int						create_pwd(char *curpath, char ***environ,
							int free_curpath);
int						cd_rule10(char *curpath, char ***environ, int flag,
							int free_curpath);

void					del_hash_bin(t_hash_bin *hash_bin);
void					del_hash(t_env *env);

typedef struct			s_builtin
{
	const char		*fn_name;
	int				(*fn_ptr)(int, char**, char ***, t_ast_node*);
}						t_builtin;

enum	e_flag_cd
{
	CD_NO_FLAG,
	CD_L,
	CD_P,
};


static const t_builtin		g_builtins[] =
{
	{"exit", &bi_exit},
	{"cd", &bi_cd},
	{"jobs", &bi_jobs},
	{"fg", &bi_fg},
	{"bg", &bi_bg},
	{"kill", &bi_kill},
	{"echo", &bi_echo},
	{"env", &bi_env},
	{"setenv", &bi_setenv},
	{"unsetenv", &bi_unsetenv},
	{"hash", &bi_hash},
	{"unset", &bi_unset},
	{"export", &bi_export},
	{"history", &bi_history},
	{"End of Builtins", NULL}
};

#endif
