# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:47:56 by mmeier            #+#    #+#              #
#    Updated: 2024/07/25 13:38:20 by mmeier           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

SRC_DIR = ./
OBJ_DIR = obj
LIBFT = ./libft/

FILES = main.c \
		utils_tokenizer.c \
		token_handling.c \
		signals.c \
		input_check.c \
		in_quotes_check.c \
		split_pipes.c \
		expansion.c \
		insert_space.c \
		free.c \
		init_proc_structs.c

BUILTINS = builtins/builtin_utils.c \
			builtins/pwd.c \

PARSING = 

TOKENIZER =

EXEC = 

SRCS = $(BUILTINS) \
		$(PARSING) \
		$(TOKENIZER) \
		$(EXEC) \
		main.c
			


OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	make -C $(LIBFT) > /dev/null
	$(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) -lft $(LDFLAGS)
	@echo "\033[32m MINISHELL has been built successfully!\033[0m"

fsanitize: 
	$(CC) -o $(NAME) $(FILES) $(LDFLAGS) -L$(LIBFT) -lft -g -fsanitize=address -static-libsan 
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)minishell.h | $(OBJ_DIR) 
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) 

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR) $(OBJ_FILES:.o=.dSYM)
	
fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
