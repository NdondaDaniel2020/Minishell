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
FILES = adjust_file_name.c \
		adjust_file_name_util.c \
		cd_1.c \
		cd_2.c \
		check_expansion_1.c \
		check_expansion_2.c \
		echo_1.c \
		echo_2.c \
		echo_3.c \
		env_1.c \
		env_2.c \
		exec_redirection.c \
		exec_redirection_util.c \
		exit_1.c \
		exit_2.c \
		export_1.c \
		export_2.c \
		export_3.c \
		export_4.c \
		lstnew_util_1.c \
		lstnew_util_2.c \
		main.c \
		master_1.c \
		master_2.c \
		other_command.c \
		pwd.c \
		redirection_util_1.c \
		redirection_util_2.c \
		redirection_util_3.c \
		redirection_util_4.c \
		redirection_util_5.c \
		redirection_util_6.c \
		redirection_util_7.c \
		redirection_util_8.c \
		redirection_util_9.c \
		redirection_util_10.c \
		signs_handler.c \
		split_2.c \
		unset.c \
		util_1.c \
		util_2.c \

SRC_FILES = $(addprefix $(SRC),$(FILES))
OBJ = $(FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror
FLAGRL = -lreadline
PLIBFT = ./libft

all:    $(NAME)

$(NAME): $(LIBFT)
	@$(CC) $(FLAGS) -c $(SRC_FILES) -I$(INCLUDE) -I$(DIR_LIBFT)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(FLAGRL) -I$(INCLUDE) -I$(DIR_LIBFT) -L$(DIR_LIBFT) -lft

$(LIBFT):
	@$(MAKE) bonus -C $(DIR_LIBFT)

r:
	@cc exmpl/run.c exmpl/run_util.c -o run -lreadline -lncurses -I$(DIR_LIBFT) -L$(DIR_LIBFT) -lft;./run

clean:
	@/bin/rm -f $(OBJ)
	@$(MAKE) clean -C $(DIR_LIBFT)

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) fclean -C $(DIR_LIBFT)

re:     fclean all

.PHONY: all clean fclean re
