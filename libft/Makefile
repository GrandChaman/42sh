# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bluff <bluff@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/19 19:26:33 by bluff             #+#    #+#              #
#    Updated: 2018/04/26 15:28:50 by fle-roy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft
PRINTF_DIR = ft_printf
GNL_DIR = gnl
LIBFT_DEP_DIR = libft_dep
PRINTF_DEP_DIR = printf_dep
GNL_DEP_DIR = gnl_dep
SRC_GNL = $(addprefix $(GNL_DIR)/, get_next_line.c)

SRC_LIBFT = $(addprefix $(LIBFT_DIR)/, ft_any.c ft_atoi.c ft_bzero.c \
ft_count_if.c ft_factorial.c ft_find_next_prime.c ft_foreach.c ft_isalnum.c \
ft_isalpha.c ft_isascii.c ft_isdigit.c ft_islowercase.c ft_isprime.c \
ft_isprint.c ft_issort.c ft_isuppercase.c ft_itoa.c ft_lstat.c \
ft_lstfind.c ft_lstforeach.c ft_lstforeach_if.c ft_lstlast.c \
ft_lstmerge.c ft_lstpush_back.c ft_lstpush_front.c ft_lstremove_if.c \
ft_lstreverse.c ft_lstsize.c ft_lstsort.c ft_lstadd.c ft_lstdel.c \
ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_map.c ft_memalloc.c \
ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
ft_memset.c ft_pow.c ft_putchar.c ft_putchar_fd.c \
ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
ft_putstr_fd.c ft_range.c ft_sqrt.c ft_strcat.c ft_strchr.c ft_strclr.c \
ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c \
ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
ft_strrchr.c ft_strrev.c ft_strcommon.c ft_strsplit.c ft_strstr.c ft_strsub.c \
ft_swap.c ft_tolower.c ft_toupper.c ft_atoi_base.c ft_iswhitespace.c \
ft_btree_apply_infix.c ft_btree_apply_suffix.c ft_btree_apply_prefix.c \
ft_btree_create_node.c ft_btree_insert_data.c ft_perror.c ft_btree_destroy.c \
ft_btree_count_node.c ft_itoa_base.c ft_numlen.c ft_getenv.c ft_free2d.c \
ft_str2ddup.c ft_haschar.c ft_free.c ft_strsplit_multi.c ft_lstdestroy.c \
dbuf_init.c dbuf_append.c dbuf_clear.c dbuf_insert.c dbuf_remove.c \
dbuf_destroy.c dbuf_substract.c dbuf_print.c ft_str3join.c ft_lstappend.c \
ft_split_whitespaces.c ft_strndup.c ft_stralike.c arrlen.c del_arr.c ft_strlcpy.c \
ft_hash.c ft_strpop.c str_isprint.c add_elem_front_dl.c del_list.c ft_strpush.c \
ft_strfjoin.c is_whitespace.c add_elem_front.c add_elem_back.c size_list.c \
cpy_arr.c ft_strindex.c ft_strndup2.c ft_strjoin_multiple.c concate_arr.c)

SRC_PRINTF = $(addprefix $(PRINTF_DIR)/, ft_printf_routine.c ft_printf.c \
		ft_printf_utils.c ft_printf_string.c ft_printf_parser.c \
		ft_printf_parameters.c ft_printf_utils2.c ft_printf_numbers.c \
		ft_printf_utils3.c ft_printf_numbers_upper.c ft_printf_wstring.c \
		ft_printf_utils4.c ft_printf_extract_dynamic_param.c \
		ft_printf_numbers2.c)

INCLUDE = include
CFLAG = -c -Wall -Wextra -Werror -O3 -I $(INCLUDE)
OBJ = obj
CC = cc
LN = ar
LFLAGS = rsc
BIN = bin
OBJ_GNL = $(SRC_GNL:$(GNL_DIR)/%.c=$(OBJ)/%.o)
OBJ_PRINTF = $(SRC_PRINTF:$(PRINTF_DIR)/%.c=$(OBJ)/%.o)
OBJ_LIBFT = $(SRC_LIBFT:$(LIBFT_DIR)/%.c=$(OBJ)/%.o)
DEP_LIBFT = $(SRC_LIBFT:$(LIBFT_DIR)/%.c=$(LIBFT_DEP_DIR)/%.d)
DEP_PRINTF = $(SRC_PRINTF:$(PRINTF_DIR)/%.c=$(PRINTF_DEP_DIR)/%.d)
DEP_GNL = $(SRC_GNL:$(GNL_DIR)/%.c=$(GNL_DEP_DIR)/%.d)

NAME = $(addprefix ./$(BIN)/, libft.a)
all: $(NAME)
test:
	@echo $(DEP_LIBFT)
	@echo $(LIBFT_DEP_DIR)
$(LIBFT_DEP_DIR)/%.d: $(LIBFT_DIR)/%.c
	@printf "\r\033[K[LIBFT] \033[1;32mGenerating deps - $<\033[0m"
	@$(CC) $(CFLAG) -MM $^ | sed -e '1s/^/$(OBJ)\//' > $@
$(PRINTF_DEP_DIR)/%.d: $(PRINTF_DIR)/%.c
	@printf "\r\033[K[PRINTF] \033[1;32mGenerating deps - $<\033[0m"
	@$(CC) $(CFLAG) -MM $^ | sed -e '1s/^/$(OBJ)\//' > $@
$(GNL_DEP_DIR)/%.d: $(GNL_DIR)/%.c
	@printf "\r\033[K[GNL] \033[1;32mGenerating deps - $<\033[0m"
	@$(CC) $(CFLAG) -MM $^ | sed -e '1s/^/$(OBJ)\//' > $@
$(OBJ)/%.o: $(LIBFT_DIR)/%.c
	@printf "\r\033[K[LIBFT] \033[1;32mBuilding $<\033[0m"
	@$(CC) $(CFLAG) $< -o $@
$(OBJ)/%.o: $(PRINTF_DIR)/%.c
	@printf "\r\033[K[PRINTF] \033[1;32mBuilding $<\033[0m"
	@$(CC) $(CFLAG) $< -o $@
$(OBJ)/%.o: $(GNL_DIR)/%.c
	@printf "\r\033[K[GNL] \033[1;32mBuilding $<\033[0m"
	@$(CC) $(CFLAG) $< -o $@
$(NAME): $(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL)
	@printf "\r\033[K[LIBFT_TOTAL] \033[1;32mLinking...\033[0m"
	@$(LN) $(LFLAGS) $(NAME) $(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL)
	@printf "\r\033[K[LIBFT_TOTAL] \033[1;32mDone!\033[0m\n"
clean:
	@rm -f $(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL)
	@printf "\r\033[K[LIBFT_TOTAL] \033[1;31mCleaned .o!\033[0m\n"
dclean:
	@rm -f $(DEP_LIBFT)
	@rm -f $(DEP_PRINTF)
	@rm -f $(DEP_GNL)
	@printf "\r\033[K[LIBFT_TOTAL] \033[1;31mCleaned .d!\033[0m\n"
fclean: clean
	@rm -f $(NAME)
	@printf "\r\033[K[LIBFT_TOTAL] \033[1;31mCleaned .a!\033[0m\n"
re:
	@$(MAKE) dclean
	@$(MAKE) fclean
	@$(MAKE) all
-include $(DEP_LIBFT)
-include $(DEP_PRINTF)
-include $(DEP_GNL)

.PHONY: all clean fclean re libft gnl printf
