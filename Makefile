# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/16 13:28:08 by fle-roy           #+#    #+#              #
#    Updated: 2018/05/04 14:21:58 by fle-roy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft
SRC_DIR = srcs
OBJ_DIR = objs
DEP_DIR = dep
INCLUDE = includes
VPATH = srcs:srcs/bang:srcs/builtins:srcs/cli:srcs/job_control:\
	srcs/lexer_parser_ast/ast/tree_build:\
	srcs/lexer_parser_ast/ast/tree_build/func_build:\
	srcs/lexer_parser_ast:srcs/lexer_parser_ast/ast:\
	srcs/lexer_parser_ast/ast/tree_exec:srcs/lexer_parser_ast/lexer:\
	srcs/lexer_parser_ast/parser:\
	srcs/lexer_parser_ast/parser/parser_funcs:srcs/sh21:\
	srcs/sh21/del:srcs/sh21/errors:srcs/sh21/print:srcs/term
SRC = bang_case.c bang_main.c bang_search.c bi_bg.c bi_cd.c bi_cd3.c \
	bi_cd_2.c bi_echo.c bi_env.c bi_exit.c bi_export.c bi_fg.c bi_hash.c \
	bi_history.c bi_history_io.c bi_jobs.c bi_kill.c bi_setenv.c bi_unset.c \
	bi_unsetenv.c ft_getenv.c ft_putenv.c ft_setenv.c ft_unsetenv.c \
	hash_table_builtins.c history_args_parser.c cli.c cli_autocomplete.c \
    cli_autocomplete_graphics.c cli_autocomplete_ht.c bi_echo_2.c\
	cli_autocomplete_local_file.c cli_autocomplete_utils.c \
	cli_autocomplete_utils2.c cli_delete.c cli_init.c cli_nav.c \
	cli_prompt.c cli_selection.c cli_spe_nav.c cli_text.c \
    cli_utils.c history.c history_loader.c history_utils.c is_correct.c \
	is_correct_ft.c jc_add.c jc_change_pgrp.c jc_cmd.c jc_create_tag.c \
	jc_delete_tag.c jc_get.c jc_set.c jc_set_job_nodes.c jc_update.c \
	jc_utils.c exec_tree.c add_str.c ast_create_node.c \
	ast_is_shell_cmd.c ast_redir_function.c case_format_word.c \
	eval_expr.c eval_expr_2.c find_var.c format_word.c \
	free_node.c ast_assignment_word.c ast_bang.c ast_compound_list.c \
	ast_for.c ast_if.c ast_pipe.c ast_until.c ast_while.c ast_word.c \
	heredoc_node.c restore_fd.c skip_var.c split_args.c split_args2.c \
	word.c func_amper.c func_and_if.c func_assignment_word.c \
	func_backslash.c func_bang.c func_case.c func_do.c func_dollar.c \
	func_done.c func_dquote.c func_dsemi.c func_elif.c func_else.c \
	func_endl.c func_eoi.c func_equal.c func_esac.c func_fi.c \
	func_for.c func_function.c func_heredoc.c func_if.c func_in.c \
	func_io_number.c func_lbrace.c func_lparen.c func_magicq.c \
	func_name.c func_newline.c func_or_if.c func_pipe.c func_quote.c \
	func_rbrace.c func_redirection.c func_rparen.c func_select.c \
	func_semi.c func_space.c func_tab.c func_then.c func_time.c \
	func_until.c func_while.c func_word.c manage_fd.c lex_create.c \
	lexer.c lexer_token_recognize.c lexutils.c lexutils_more.c \
	on_subshell.c subshell_exec.c parser.c assert_lex.c assignement_word.c \
	case_clause.c case_clause_sequence.c case_command.c command.c \
	compound_list.c elif_clause.c for_command.c function_def.c group_command.c \
	if_command.c is_token.c list.c list0.c list1.c list_terminator.c \
	newline_list.c pattern_list.c pipeline.c pipeline_command.c program.c \
	redirection.c select_command.c shell_command.c simple_command.c \
	simple_command_element.c simple_list.c simple_list1.c subshell.c \
	timespec.c word_list.c main.c del_ast.c del_env.c del_hash.c del_lex.c \
	del_redir.c del_sh21.c errors.c input_piped_script.c ast_print.c \
	env_usage.c print_env.c print_lex.c set_debugtty.c remove_char.c \
	set_sh21.c sh21_exec.c sh21_exec_builtins.c sh21_exec_fork.c \
	signal_handler.c term_command.c terminal_settings.c

LIBFT_INCLUDE = $(LIBFT_DIR)/include
CFLAG = -Wall -Wextra -Werror -I $(LIBFT_INCLUDE) -I $(INCLUDE)
CC = cc
LFLAG = -ltermcap
BIN = bin
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(SRC:%.c=$(DEP_DIR)/%.d)
NAME = 42sh
NAME_UP = 42SH
LIBFT = $(addprefix $(LIBFT_DIR)/, bin/libft.a)

all: lib $(NAME)
lib:
	@$(MAKE) -C $(LIBFT_DIR)
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
$(OBJ_DIR)/%.o: %.c
	@printf "\r\033[K[$(NAME_UP)] \033[1;32mBuilding $<\033[0m"
	@$(CC) $(CFLAG) -c $(CFLAG) $< -o $@
$(DEP_DIR)/%.d: %.c
	@printf "\r\033[K[$(NAME_UP)] \033[1;32mGenerating dependencies - $<\033[0m"
	@$(CC) $(CFLAG) -MM $^ | sed -e '1s/^/$(OBJ_DIR)\//' > $@
$(NAME): $(LIBFT) $(SRC_LIBFT) $(SRC_PRINTF) $(SRC_GNL) $(OBJ)
	@printf "\r\033[K[$(NAME_UP)] \033[1;32mLinking...\033[0m"
	@$(CC) $(CFLAG) $(LFLAG) -o $(NAME) $(LIBFT) $(OBJ)
	@printf "\r\033[K[$(NAME_UP)] \033[1;32mDone!\033[0m\n"
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJ)
	@printf "[$(NAME_UP)] \033[1;31mCleaned .o!\033[0m\n"
dclean:
	@rm -f $(DEP)
	@printf "[$(NAME_UP)] \033[1;31mCleaned .d!\033[0m\n"
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@printf "[$(NAME_UP)] \033[1;31mCleaned .a!\033[0m\n"
re:
	@$(MAKE) fclean
	@$(MAKE) all
-include $(DEP)
.PHONY: all clean fclean re dclean
