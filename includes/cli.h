/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:56:03 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/26 13:49:43 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CLI_H
# define FT_CLI_H

# include <sys/ioctl.h>
# include "libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <term.h>
# include <unistd.h>
# include <time.h>
# include <sys/param.h>
# include <fcntl.h>
# include <signal.h>
# define T_ESCAPE 27
# define T_ENTER 10
# define T_TAB 9
# define T_BACKSPACE 127
# define T_DELETE 2117294875
# define T_END 4610843
# define T_HOME 4741915
# define T_LARR 4479771
# define T_RARR 4414235
# define T_BARR 4348699
# define T_TARR 4283163
# define T_SLARR 74982532143899
# define T_SRARR 73883020516123
# define T_SBARR 72783508888347
# define T_STARR 71683997260571
# define T_ALT_LEFT 1146821403
# define T_ALT_RIGHT 1130044187
# define T_ALT_C 42947
# define T_ALT_V 10127586
# define T_ALT_X 8948194
# define T_CTRL_A 1
# define T_CTRL_C 3
# define T_CTRL_D 4
# define T_CTRL_E 5
# define T_CTRL_L 12
# define T_ALT_UP 1096489755
# define T_ALT_DOWN 1113266971
# define SHIFT_MASK 70584485632795
# define ANSI_COLOR_B_RED      "\x1b[1;31m"
# define ANSI_COLOR_B_GREEN    "\x1b[1;32m"
# define TC_MOVELEFT "le"
# define TC_MOVERIGHT "nd"
# define TC_DELETE "dc"
# define TC_NDELETE "DC"
# define TC_MOVENLEFT "LE"
# define TC_INSERTNCHAR "IC"
# define TC_GOTONEXTLINE "nw"
# define TC_SAVECURPOS "sc"
# define TC_RESETCURPOS "rc"
# define TC_MOVEDOWN "do"
# define TC_MOVEUP "up"
# define TC_MOVENUP "UP"
# define TC_MOVENDOWN "DO"
# define TC_MOVENRIGHT "RI"
# define TC_CARRIAGERETURN "cr"
# define TC_CLEAR_FROM_HERE "cd"
# define TC_REVERSEVIDEO "mr"
# define TC_RESETGRAPHICS "me"
# define TC_UNDERLINE_ON "us"
# define TC_UNDERLINE_OFF "ue"
# define TC_CLEAR "cl"
# define TC_BELL "vb"
# define ABS(x) ((x) < 0 ? ((x) * -1) : (x))
# define SH_HIST_MAX_SIZE 100
# define EF_OK 1
# define EF_DENIED 2
# define EF_NOTFOUND 5

typedef	struct			s_bin_hash
{
	unsigned int		index;
	char				*name;
	char				*path;
	char				can_exec;
}						t_bin_hash;

typedef	struct			s_bin_hash_table
{
	t_bin_hash			*table;
	unsigned int		size;
}						t_bin_hash_table;

typedef struct			s_ft_sh
{
	unsigned int		x_size;
	unsigned int		y_size;
	unsigned int		prompt_size;
	t_dbuf				buf;
	unsigned int		cursor;
	unsigned int		alt_cursor;
	unsigned int		select_start;
	int					select_size;
	char				*select;
	unsigned char		is_a_tty;
	t_list				*history;
	long				history_size;
	long				history_pos;
	char				*history_last;
	char				is_alt_shell;
	t_list				*autocomplete;
	t_list				*autocomplete_cusor;
	int					autocomplete_padding;
	t_bin_hash_table	*ht;
}						t_ft_sh;

typedef struct			s_env_var
{
	char				*key;
	char				*value;
}						t_env_var;

typedef struct			s_ft_autoc_entry
{
	char				*name;
	char				*color;
	char				undeline;
	int					x_pos;
	int					y_pos;
}						t_ft_autoc_entry;

typedef	struct			s_ft_touch
{
	unsigned long		touch;
	void				(*f)(unsigned long);
}						t_ft_touch;

typedef	struct			s_ft_hist_entry
{
	char				*command;
	long				timestamp;
}						t_ft_hist_entry;

char					*check_correct(char *toto);

t_bin_hash_table		*load_bin_into_hash_table(t_list *env);
int						compare_with_key(void *e1, void *e2);
void					free_hash_table(t_bin_hash_table **ht);
unsigned long			dj2b_hash(char *str);
t_bin_hash				*get_elem_from_ht(t_bin_hash_table *ht, char *name);
void					collect_data_ht(t_list **list, char *str_part);
t_ft_sh					*get_ft_shell(void);
int						is_env_correct(void);
void					apply_terminal_setting(int def);
int						display_prompt(int last_result);
char					*read_command(char *prompt, int status, int heredoc);
void					exec_term_command(const char *code);
void					exec_term_command_p(const char *code, int p1, int p2);
void					spt_arrow(unsigned long touch);
void					get_screen_size(int sig);
int						ft_nputstr(char *str, int n);
void					move_in_terminal(unsigned long touch);
void					backspace_command(unsigned long touch);
void					update_stdout(t_ft_sh *sh, int offset);
void					delete_command(unsigned long touch);
void					(*g_special_char_f(unsigned long val))(unsigned long);
void					nav_touch_received(unsigned long touch);
void					move_select(unsigned long touch);
void					copy_select(unsigned long touch);
void					paste_select(unsigned long touch);
void					cut_select(unsigned long touch);
void					cli_loader(int destroy);
int						load_history(t_ft_sh *sh, int unload);
void					add_to_history(t_ft_sh *sh, char *cmd);
int						is_alt_shell_begin(void);
void					history_nav(unsigned long touch);
void					cli_reset_cursor(t_ft_sh *sh);
void					sh_clear_screen(unsigned long rchar);
void					vertical_nav(unsigned long touch);
char					*search_history_nav(t_ft_sh *sh, char *search, int up);
void					collect_data(char *str_part);
void					ft_sh_autocomplete(unsigned long touch);
unsigned int			cursor_new_origin(t_ft_sh *sh);
void					delete_autocomplete_entry(void *el, size_t size);
void					move_in_autocompletion(unsigned long touch);
void					cancel_autocompletion(t_ft_sh *shell,
	unsigned long rchar);
void					prepare_autocomplete(t_ft_sh *sh, t_list *list,
	unsigned int save_cur);
void					insert_in_cli(char *str);
void					print_normal_touch(t_ft_sh *sh, unsigned long rchar);
void					collect_data_local_file(t_list **list, char *str_part);
int						cmp_autoc_entry(void *e1, void *e2);
void					ready_cursor_autocompletion();
void					delete_autocomplete_entry(void *el, size_t size);
void					display_autocomplete(t_ft_sh *sh, t_list *list);
void					prepare_autocomplete(t_ft_sh *sh, t_list *list,
	unsigned int save_cur);
int						get_autocomplete_el_with(t_list *list);
void					setpos_autocomplete(t_ft_sh *sh);
void					cancel_selection(t_ft_sh *shell, unsigned long rchar);
void					print_normal_touch(t_ft_sh *sh, unsigned long rchar);
int						display_prompt(int last_result);
void					prompt_select(char *prompt, int status, int heredoc);
int						display_prompt(int last_result);
void					print_normal_touch(t_ft_sh *sh, unsigned long rchar);
void					delete_hist_entry(void *entry, size_t size);
void					trim_history(t_ft_sh *sh);
void					vertical_nav(unsigned long touch);
void					skip_in_terminal(unsigned long touch);
void					home_or_end_touch(unsigned long touch);
int						is_last_char_a_nl(void);
int						read_history(t_ft_sh *sh, int fd);
void					write_history(t_ft_sh *sh, int fd, int should_delete);
void					parse_and_add_to_history(t_ft_sh *sh, char *line);
char					*get_history_file(void);
char					*escape_operator(char *str);
void					set_up_default_signal(void);
void					signal_c(int sig);
void					ignore_signal(int sig);

static t_ft_touch		g_ft_touch_list[] =
{
	{T_TAB, ft_sh_autocomplete},
	{T_ENTER, ft_sh_autocomplete},
	{T_BACKSPACE, backspace_command},
	{T_DELETE, delete_command},
	{T_HOME, nav_touch_received},
	{T_CTRL_A, nav_touch_received},
	{T_CTRL_E, nav_touch_received},
	{T_END, nav_touch_received},
	{T_LARR, nav_touch_received},
	{T_RARR, nav_touch_received},
	{T_BARR, history_nav},
	{T_TARR, history_nav},
	{T_SLARR, nav_touch_received},
	{T_SRARR, nav_touch_received},
	{T_SBARR, nav_touch_received},
	{T_STARR, nav_touch_received},
	{T_ALT_LEFT, move_select},
	{T_ALT_RIGHT, move_select},
	{T_ALT_C, copy_select},
	{T_ALT_X, cut_select},
	{T_ALT_V, paste_select},
	{T_CTRL_L, sh_clear_screen},
	{T_ALT_UP, vertical_nav},
	{T_ALT_DOWN, vertical_nav},
	{0, NULL}
};

#endif
