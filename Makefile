# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:47:56 by mmeier            #+#    #+#              #
#    Updated: 2024/08/05 09:43:07 by mmeier           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

SRC_DIR = ./
OBJ_DIR = ./obj/
LIBFT = ./libft/
INCLUDES = -I./

FILES = main.c \
		check_input/input_check.c \
		check_input/in_quotes_check.c \
		lexing/utils_tokenizer_a.c \
		lexing/utils_tokenizer_b.c \
		lexing/token_handling.c \
		lexing/expansion.c \
		lexing/insert_space.c \
		lexing/remove_quotes.c \
		parsing/init_proc_structs.c \
		parsing/path.c \
		free/free_a.c \
		free/free_b.c \
		execution/exec.c \
		execution/redirects.c \
		signal/signals.c \
		builtins/env.c \
#		builtins/builtin_utils.c \
#		builtins/pwd.c \

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	make -C $(LIBFT) > /dev/null
	$(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) -lft $(LDFLAGS)
	@echo "\033[32m MINISHELL has been built successfully!\033[0m"

fsanitize: 
	$(CC) -o $(NAME) $(FILES) $(LDFLAGS) -L$(LIBFT) -lft -g -fsanitize=address -static-libsan 
	
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
	@mkdir -p $(OBJ_DIR)signal

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR) $(OBJ_FILES:.o=.dSYM)
	
fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re