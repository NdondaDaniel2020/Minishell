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
DIR_LIBFT = ./libft/
LIBFT = $(DIR_LIBFT)libft.a
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

$(NAME): $(LIBFT)
	$(CC) $(FLAGS) -c $(SRC_FILES) -I$(INCLUDE) -I$(DIR_LIBFT)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(FLAGRL) -I$(INCLUDE) -I$(DIR_LIBFT) -L$(LIBFT)

$(LIBFT):
	$(MAKE) bonus -c $(DIR_LIBFT)

r:
	cc exmpl/run.c -o run -lreadline -lncurses ;./run

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re:     fclean all

.PHONY: all clean fclean re
