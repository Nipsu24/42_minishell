# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:47:56 by mmeier            #+#    #+#              #
#    Updated: 2024/09/06 11:44:52 by mmeier           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

SRC_DIR = ./
OBJ_DIR = ./obj/
LIBFT = ./libft/
INCLUDES = -I/usr/local/opt/readline/include -I./

FILES = main.c \
		utils.c \
		check_input/input_check_a.c \
		check_input/input_check_b.c \
		check_input/in_quotes_check.c \
		lexing/utils_tokenizer_a.c \
		lexing/utils_tokenizer_b.c \
		lexing/token_handling.c \
		lexing/expansion_a.c \
		lexing/expansion_b.c \
		lexing/expansion_c.c \
		lexing/insert_space.c \
		lexing/remove_quotes.c \
		parsing/init_proc_structs_a.c \
		parsing/init_proc_structs_b.c \
		parsing/init_proc_structs_c.c \
		parsing/path_a.c \
		parsing/path_b.c \
		parsing/alloc_file_name.c \
		parsing/create_heredoc_a.c \
		parsing/create_heredoc_b.c \
		free/free_a.c \
		free/free_b.c \
		free/free_c.c \
		execution/exec.c \
		execution/redirects.c \
		execution/redirect_utils.c \
		execution/exec_utils.c \
		signals/signals.c \
		signals/termios.c \
		execution/child_exec.c \
		execution/parent_exec.c \
		execution/exec_builtins.c \
		execution/child_here_red.c \
		builtins/env.c \
		builtins/builtin_utils.c \
		builtins/pwd.c \
		builtins/echo.c \
		builtins/export.c \
		builtins/unset.c \
		builtins/cd.c \
		builtins/exit.c \

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	make -C $(LIBFT) > /dev/null
	$(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) -lft $(LDFLAGS)
	@echo "\033[32m MINISHELL has been built successfully!\033[0m"

fsanitize: 
	$(CC) -o $(NAME) $(FILES) $(LDFLAGS) -L$(LIBFT) $(INCLUDES) -lft -g -fsanitize=address -static-libsan 
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)minishell.h | $(OBJ_DIR) 
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)builtins
	@mkdir -p $(OBJ_DIR)check_input
	@mkdir -p $(OBJ_DIR)lexing
	@mkdir -p $(OBJ_DIR)parsing
	@mkdir -p $(OBJ_DIR)execution
	@mkdir -p $(OBJ_DIR)free
	@mkdir -p $(OBJ_DIR)signals

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR) $(OBJ_FILES:.o=.dSYM)
	
fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re