/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 14:17:28 by fbertoia          #+#    #+#             */
/*   Updated: 2018/03/12 15:58:20 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <sys/ioctl.h>
# include <stdlib.h>
# include <stdint.h>

# define BUFF_SIZE_READ 8u
# define SH21_ARROW_LEFT 4479771ul
# define SH21_ARROW_RIGHT 4414235ul
# define SH21_ARROW_UP 4283163ul
# define SH21_CTRL_P 16
# define SH21_ARROW_DOWN 4348699ul
# define SH21_CTRL_N 14
# define SH21_DEL_BACKWARD 127ul
# define SH21_DEL_BACKWARD_CTR_H 8
# define SH21_DEL_FORWARD 2117294875ul
# define SH21_CTRL 12
# define SH21_CTRC 3
# define SH21_CTRK 11
# define SH21_CTRE 5
# define SH21_CTRT 20
# define SH21_ALTC 42947
# define SH21_ALTV 10127586
# define SH21_WORD_BEG 1146821403
# define SH21_WORD_END 1130044187
# define SH21_BEG_LINE 4741915
# define SH21_END_LINE 4610843
# define SH21_LINE_UP 1096489755
# define SH21_LINE_DOWN 1113266971
# define SH21_NEWLINE 10
# define SH21_EOF 4

typedef struct s_sh21	t_sh21;
typedef struct			s_pos
{
	int x;
	int y;
}						t_pos;

typedef struct			s_dlinked
{
	struct s_dlinked	*next;
	struct s_dlinked	*previous;
	char				*command;
}						t_dlinked;

typedef struct			s_history
{
	t_dlinked			*list;
	t_dlinked			*needle;
}						t_history;

enum 	e_signal
{
	SIGNAL_ENTER,
	SIGNAL_CTRLD,
	SIGNAL_CTRLC,
	SIGNAL_NONE,
};

enum 	e_mode
{
	REGULAR,
	HEREDOC,
};

typedef struct			s_input
{
	char				*buff;
	char				*clipboard;
	char				*historic_buff;
	char				*prompt;
	char				*tmp_buff;
	int					debug_tty;
	int					flag_prompt;
	int					in;
	int					tty;
	int					history_fd;
	int					history_line_nb;
	t_pos				pos;
	t_history			history;
	size_t				buff_sz;
	size_t				buff_len;
	size_t				cur_pos;
	size_t				prompt_sz;
	struct winsize		winsize;
	uint64_t			read;
	int					start_select;
	int					end_select;
	int					is_select;
	int					last_mv;
	enum e_signal		signal;
	enum e_mode			mode;
	char 				quote;
}						t_input;

void					set_cursor(int cols, int rows);
void					mv_cursor(int cols, int rows);
void					goto_end_of_prompt(t_input *input);

void					clear_command(t_input *input);
void					display_input(t_input *input);
void					rt_cursor(t_input *input);
void					sv_cursor(t_input *input, int beg, int end);

void					del_input(t_input *input);
int						input_get(t_input *input);
void					input_init(t_input *input, char c);
void					init_prompt(t_input *input, char c);
void					input_putc(t_input *input, int c);
int						input_call_function(t_input *input);
void					opentty(t_input *input);
int						my_putchar(int c);

int						arrow_left(t_input *input);
int						arrow_right(t_input *input);
int						arrow_up(t_input *input);
int						arrow_down(t_input *input);
int						sh21_clear_screen(t_input *input);
int						controlc(t_input *input);
int						controlk(t_input *input);
int						controlt(t_input *input);
int						sh21_newline(t_input *input);
int						sh21_eof(t_input *input);
int						delete_back(t_input *input);
int						delete_forw(t_input *input);
int						write_char(t_input *input);
int						word_beg(t_input *input);
int						word_end(t_input *input);
int						beg_line(t_input *input);
int						end_line(t_input *input);
int						line_up(t_input *input);
int						line_down(t_input *input);
int						alt_right(t_input *input);
int						delete_select(t_input *input);
int						controle(t_input *input);
int						set_uinput(t_input *input);

void					clear_history(t_input *input);
t_dlinked				*add_history_list(char *command);
void					add_history_file(t_input *input, char *command);
void					print_history(t_dlinked *history_list, int fd);

enum	e_fn_flags
{
	NNOP = 1 << 0,
	SAVE = 1 << 1,
	CLEAR = 1 << 2,
	DISPLAY = 1 << 3,
	RESTORE = 1 << 4
};

typedef struct			s_input_function_call
{
	uint64_t			key;
	int					(*call_function)(t_input*);
	uint16_t			flags;
}						t_input_function_call;

static t_input_function_call g_read_function[] =
{
	{SH21_ARROW_LEFT, arrow_left, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_ARROW_RIGHT, arrow_right, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_ARROW_UP, arrow_up, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_CTRL_P, arrow_up, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_ARROW_DOWN, arrow_down, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_CTRL_N, arrow_down, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_CTRL, sh21_clear_screen, NNOP},
	{SH21_CTRC, controlc, NNOP},
	{SH21_CTRK, controlk, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_CTRE, controle, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_CTRT, controlt, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_NEWLINE, sh21_newline, NNOP},
	{SH21_EOF, sh21_eof, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_DEL_BACKWARD, delete_back, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_DEL_BACKWARD_CTR_H, delete_back, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_DEL_FORWARD, delete_forw, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_WORD_BEG, word_beg, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_WORD_END, word_end, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_BEG_LINE, beg_line, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_END_LINE, end_line, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_LINE_UP, line_up, SAVE | CLEAR | DISPLAY | RESTORE},
	{SH21_LINE_DOWN, line_down, SAVE | CLEAR | DISPLAY | RESTORE},
	{0, NULL, NNOP}
};

#endif
