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
		echo.c \
		echo_util.c \
		env_1.c \
		env_2.c \
		environment_variation_expansion_1.c \
		environment_variation_expansion_2.c \
		environment_variation_expansion_util.c \
		exec_all_redirect_directions.c \
		exec_main_redirect.c \
		exec_redirect_directions.c \
		exec_redirection.c \
		exec_redirection_util.c \
		execute_commands_without_pipe.c \
		execute_commands_with_pipe_util.c \
		execute_commands_with_pipe.c \
		exit_1.c \
		exit_2.c \
		export_1.c \
		export_2.c \
		export_3.c \
		export_4.c \
		heredoc.c \
		heredoc_pipe.c \
		heredoc_pipe_util.c \
		heredoc_quotes.c \
		heredoc_util.c \
		lstnew_util_1.c \
		lstnew_util_2.c \
		main.c \
		other_command.c \
		other_command_util.c \
		pwd.c \
		redirection.c \
		redirection_util_10.c \
		redirection_util_1.c \
		redirection_util_2.c \
		redirection_util_3.c \
		redirection_util_4.c \
		redirection_util_5.c \
		redirection_util_6.c \
		redirection_util_7.c \
		redirection_util_8.c \
		redirection_util_9.c \
		signs_handler.c \
		split_2.c \
		unset.c \
		util_1.c \
		util_2.c \
		util_3.c \
		util_4.c \
		util_5.c \

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

rr:
	@cc $(FLAGS) exmpl/run.c exmpl/run_util.c -o run -lreadline -lncurses -I$(DIR_LIBFT) -L$(DIR_LIBFT) -lft;./run

clean:
	@/bin/rm -f $(OBJ)
	@$(MAKE) clean -C $(DIR_LIBFT)

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) fclean -C $(DIR_LIBFT)

re:     fclean all

.PHONY: all clean fclean re
