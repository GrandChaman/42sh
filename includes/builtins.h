/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:54:39 by hfontain          #+#    #+#             */
/*   Updated: 2018/03/19 20:37:03 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "sh21.h"

int						ft_echo(char *argv[]);
int						find_bin_paths(t_env *env, char ***environ);

char					*ft_getenv(const char *name, char ***environ);
int						ft_unsetenv(const char *name, char ***environ);
int						ft_putenv(const char *str, char ***environ);
int						ft_setenv(const char *name, const char *value,
						int override, char ***environ);
int						print_env(char **env);
int						env_usage(char c, int option);

int						bi_cd(int argc, char **argv, char ***environ);
int						bi_echo(int argc, char **argv, char ***environ);
int						bi_env(int argc, char **argv, char ***environ);
int						bi_exit(int argc, char **argv, char ***environ);
int						bi_setenv(int argc, char **argv, char ***environ);
int						bi_unsetenv(int argc, char **argv, char ***environ);
int						bi_hash(int argc, char **argv, char ***environ);
int						bi_export(int argc, char **argv, char ***environ);
int						bi_unset(int argc, char **argv, char ***environ);

void					del_hash_bin(t_hash_bin *hash_bin);
void					del_hash(t_env	*env);

typedef struct			s_builtin
{
	const char		*fn_name;
	int				(*fn_ptr)(int, char**, char ***);
}						t_builtin;

static const t_builtin	g_builtins[] =
{
	{"exit", &bi_exit},
	{"cd", &bi_cd},
	{"echo", &bi_echo},
	{"env", &bi_env},
	{"setenv", &bi_setenv},
	{"unsetenv", &bi_unsetenv},
	{"hash", &bi_hash},
	{"unset", &bi_unset},
	{"export", &bi_export},
	{"End of Builtins", NULL}
};

#endif
