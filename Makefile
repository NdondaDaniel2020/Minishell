# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 01:32:20 by nmatondo          #+#    #+#              #
#    Updated: 2024/08/07 16:44:49 by nmatondo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = ./minishell
SRC = ./src/
INCLUDE = ./include
FILES = main.c

SRC_FILES = $(addprefix $(SRC),$(FILES))
OBJ = $(FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror
FLAGRL = -lreadline
PLIBFT = ./libft

all:    $(NAME)

$(NAME):
	$(CC) $(FLAGS) -c $(SRC_FILES) -I$(INCLUDE)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(FLAGRL) -I$(INCLUDE)

r:
	cc exmpl/run.c -o run -lreadline -lncurses ;./run

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re:     fclean all

.PHONY: all clean fclean re
