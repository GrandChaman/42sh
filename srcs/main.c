/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:26:22 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/17 17:00:28 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ast.h"
#include "lexer.h"
#include "cli.h"
#include "libft.h"

t_lex		*g_err_lex;


static char	*ft_strpushm(char *str, size_t idx, char c)
{
	char	*new;
	size_t	ln;

	if (!str)
	{
		new = ft_strnew(1);
		new[0] = c;
		return (new);
	}
	ln = ft_strlen(str);
	if (ln == 0)
	{
		new = ft_strnew(1);
		new[0] = c;
		ft_strdel(&str);
		return (new);
	}
	if (idx > ln)
		return (str);
	new = ft_strnew(ln + 1);
	ft_strncpy(new, str, idx);
	ft_strncat(new, &c, 1);
	ft_strcat(new, str + idx);
	ft_strdel(&str);
	return (new);
}

int	str_replace(char **src, char *tok, char *new)
{
	char	*ptr;
	if ((ptr = ft_strstr(*src, tok)))
	{
		int	offset = (int)(ptr - *src);
		int	nb = ft_strlen(tok);
		while (nb)
		{
			*src = ft_strpop(*src, offset);
			--nb;
		}
		char *tmp = new;
		while (*tmp)
		{
			*src = ft_strpushm(*src, offset + nb, *tmp);
			++nb;
			++tmp;
		}
		return (1);
	}
	return (0);
}

int is_ok(char *str, int bef, int aft)
{
	if (str[bef] != '\\' && str[bef] != '\''
		&& str[aft] != '"' && !is_whitespace(str[aft]))
		return (1);
	return (0);
}

char	*get_history_at(int i)
{
	t_ft_sh *sh = get_ft_shell();
	t_list	*tmp, *first;// *last;
	const int len = ft_lstsize(sh->history);
	int mv;

	if (i < 0)
		mv = -i;
	else if (i > 0)
		mv = len - i;
	else
		mv = 0;

	first = sh->history;
	tmp = first;
	while (tmp && mv--)
	{
		first = tmp;
		tmp = tmp->next;
	}
	return ((t_ft_hist_entry*)first->content)->command;
}

static int bbb(char *str)
{
	int i = 0;
	int aa;
	char *tmp = str;
	int err;
	while (*tmp)
	{
		if (str[i] == '!' && str[i + 1] == '!' && is_ok(str, i - 1, i + 1))
			err = str_replace(&str, "!!", get_history_at(0));
		else if (str[i] == '!'
					&& is_ok(str, i - 1, i + 1)
					&& ((str[i + 1] == '-' && ft_isdigit(str[i + 2]))
						|| ft_isdigit(str[i + 1])))
		{
			aa = ft_atoi(&str[i + 1]);
			char	*j = ft_strjoin("!", ft_itoa(aa));
			err = str_replace(&str, j, get_history_at(aa));
			free(j);
		}
		++i;
		++tmp;
	}
	err ? ft_printf("%s\n", str) : (0);
	return (err);
}

static void	ignore_signal(int sig)
{
	(void)sig;
}

static void	main_loop(t_sh21 *sh21, t_ft_sh *shell)
{
	int		fb;
	char	*cmd;

	fb = 0;
	while (42)
	{
		if (((cmd = read_command(NULL, sh21->ret, 0, (!fb ? fb++ : fb))) == NULL))
			break ;
		int x = bbb(cmd);
		x ? (0) : add_to_history(shell, cmd);
		sh21->buf = cmd;
		lexer(sh21);
		if (parser(sh21->lex) && sh21->signal != T_CTRL_C)
			sh21_get()->ret = exec_tree(sh21->tree.root_node);
		del_sh21();
		free(cmd);
	}
}

int			main(void)
{
	t_ft_sh			*shell;
	t_sh21			*sh21;
	extern char		**environ;

	sh21 = sh21_init(environ);
	shell = get_ft_shell();
	shell->ht = NULL;
	signal(SIGINT, ignore_signal);
	if (!is_env_correct())
		return (1);
	cli_loader(0);
	if (!shell->is_a_tty)
	{
		cli_loader(1);
		return (1);
	}
	main_loop(sh21, shell);
	del_sh21_exit();
	return (0);
}
