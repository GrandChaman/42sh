# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/16 13:28:08 by fle-roy           #+#    #+#              #
#    Updated: 2018/04/05 16:42:23 by fle-roy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft
SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep
INCLUDE = include
VPATH = src:src/cli:src/term
SRC = main.c cli.c cli_init.c \
terminal_settings.c cli_selection.c term_command.c cli_utils.c \
cli_nav.c cli_delete.c history_loader.c cli_autocomplete.c \
cli_autocomplete_utils.c history.c \
cli_autocomplete_graphics.c cli_autocomplete_local_file.c cli_text.c \
cli_prompt.c history_utils.c cli_spe_nav.c cli_autocomplete_ht.c
LIBFT_INCLUDE = $(LIBFT_DIR)/include
CFLAG = -g3 -Wall -Wextra -Werror -I $(INCLUDE) -I $(LIBFT_INCLUDE)
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
	@$(CC) $(CFLAG) -c $< -o $@
$(DEP_DIR)/%.d: %.c
	@printf "\r\033[K[$(NAME_UP)] \033[1;32mGenerating dependencies - $<\033[0m"
	@$(CC) $(CFLAG) -MM $^ | sed -e '1s/^/$(OBJ_DIR)\//' > $@
$(NAME): $(LIBFT) $(SRC_LIBFT) $(SRC_PRINTF) $(SRC_GNL) $(OBJ)
	@printf "\r\033[K[$(NAME_UP)] \033[1;32mLinking...\033[0m"
	@$(CC) $(LFLAG) -o $(NAME) $(LIBFT) $(OBJ)
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
