# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 13:12:46 by nmatondo          #+#    #+#              #
#    Updated: 2024/07/26 11:42:47 by nmatondo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

B = 0;
NAME = libft.a
FILES = ft_itoa.c \
		ft_atoi.c \
		ft_split.c \
		ft_bzero.c \
		ft_strlen.c \
		ft_memset.c \
		ft_memcpy.c \
		ft_strchr.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \

BFILES = ft_lstmap.c \
		 ft_lstnew.c \
		 ft_lstsize.c \
	 	 ft_lstlast.c \
		 ft_lstiter.c \
	 	 ft_lstclear.c \
		 ft_lstdelone.c \
		 ft_lstadd_back.c \
		 ft_lstadd_front.c \
		 ft_nblen.c \
		 ft_putstr.c \
		 ft_printf.c \
		 ft_putchar.c \
		 ft_put_end_mem.c \
		 ft_putnbr_base.c \
		 ft_put_unsigned.c \
		 get_next_line.c \
		 get_next_line_utils.c \
		 ft_findchar.c \
		 ft_initstr.c

OBJS = $(FILES:.c=.o)
BOBJS = $(BFILES:.c=.o)
FLAGS = -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):
ifeq ($(B), 0)
	@gcc $(FLAGS) -c $(FILES)
	@ar rcs $(NAME) $(OBJS)
else
	@gcc $(FLAGS) -c $(FILES) $(BFILES)
	@ar rcs $(NAME) $(OBJS) $(BOBJS)
endif

bonus: 
	@$(MAKE) B=1

clean:
	@/bin/rm -f $(OBJS) $(BOBJS)

fclean:	clean
	@/bin/rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
