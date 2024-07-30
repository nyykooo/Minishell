# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 17:37:50 by ncampbel          #+#    #+#              #
#    Updated: 2024/07/30 18:53:41 by ncampbel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = main analyze_input signals pipe heredoc

SRC_BUILTINS = cd echo env equal export unset exec pwd exit

SRC_FREE_ERROR_EXIT = free error

SRC_PARSE = parsing

SRC_PARSE_TOKEN = tokenizer token_creation token_analyze

SRC_PARSE_QUOTES = quotes_functions

SRC_PARSE_PIPE = handle_pipe

SRC_PARSE_INPUT = input_handle

SRC_PARSE_COMMAND = create_commands analyze_argument

SRC_PARSE_EXPANSION = expansion dolar tildes hashtag

SRC_VARIABLES = var underline_var question_var var_operations1 var_operations2

SRC = $(addsuffix .c, $(addprefix src/, $(SRC_DIR))) \
	$(addsuffix .c, $(addprefix src/builtins/, $(SRC_BUILTINS))) \
	$(addsuffix .c, $(addprefix src/free_error_exit/, $(SRC_FREE_ERROR_EXIT))) \
	$(addsuffix .c, $(addprefix src/parse/, $(SRC_PARSE))) \
	$(addsuffix .c, $(addprefix src/parse/token/, $(SRC_PARSE_TOKEN))) \
	$(addsuffix .c, $(addprefix src/parse/redirect/, $(SRC_PARSE_REDIRECT))) \
	$(addsuffix .c, $(addprefix src/parse/quotes/, $(SRC_PARSE_QUOTES))) \
	$(addsuffix .c, $(addprefix src/parse/pipe/, $(SRC_PARSE_PIPE))) \
	$(addsuffix .c, $(addprefix src/parse/input/, $(SRC_PARSE_INPUT))) \
	$(addsuffix .c, $(addprefix src/parse/command/, $(SRC_PARSE_COMMAND))) \
	$(addsuffix .c, $(addprefix src/parse/expansion/, $(SRC_PARSE_EXPANSION))) \
	$(addsuffix .c, $(addprefix src/variables/, $(SRC_VARIABLES)))

LIBFT = "libs/libft/libft.a"

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	make -C libs/libft -s

clean:
	rm -f $(OBJ)
	make -C libs/libft clean -s

fclean: clean
	rm -f $(NAME)
	make -C libs/libft fclean -s

re: fclean all

valgrind:
		valgrind --suppressions=study/readline.supp --leak-check=full --trace-children=yes --track-fds=yes --show-leak-kinds=all ./${NAME}

envvalgrind:
		valgrind --suppressions=study/readline.supp --leak-check=full --trace-children=yes --track-fds=yes --show-leak-kinds=all env -i ./${NAME}

.PHONY: all clean fclean re

.SILENT: