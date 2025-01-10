/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

#include "libft.h"
#include <term.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <termios.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>

typedef struct s_new_list
{
	int					item;
	char				**content;
	struct s_new_list	*next;
}						t_new_list;

typedef struct s_data
{
	int			write_on_the_pipe;
	int			read_in_the_pipe;
	bool		is_pipe;
	bool		space;
	bool		automatic_input;
	char		*command;
	char		*output;
	char		*put_amb;
	char		**path;
	char		**envp;
	char		**redirection_matrix;
	t_new_list	*list;
}				t_data;

typedef struct s_valid
{
	bool	is_quota;
	bool	is_transition;
}			t_valid;

typedef struct s_split
{
	int		len;
	int		in_quotes;
	int		substr_count;
	char	**result;
	char	*start;
	char	*end;
} 			t_split;

typedef struct s_extract
{
	char	*string;
	int		start;
	int		end;
	int		returned;
}			t_extract;

typedef struct s_var_red
{
	char		**list_error;
	t_extract	**extract_matrix;
}				t_var_red;

typedef struct s_two_extract
{
	int			len_1;
	int			len_2;
	t_extract	*ext1;
	t_extract	*ext2;
}				t_two_extract;

typedef struct s_index
{
	int			index;
	t_extract	*content;
}				t_index;

typedef struct s_index_str
{
	int			index;
	char		*str;
}				t_index_str;

void		init_data(t_data *data);
void		free_matrix(char **matrix);
char		**split_2(char *str, char chr);
void		ft_lstnew_addback(t_new_list **lst, t_new_list *new);
void		ft_lstnew_addfront(t_new_list **lst, t_new_list *new);
void		ft_lstnew_addafter_pos( t_new_list **lst, t_new_list *ref, t_new_list *new);
t_new_list	*ft_lstnew_new(char **content);
int			ft_lstnew_size(t_new_list *lst);
void		ft_lstnew_free(char **matrix, t_new_list *removed);
void		ft_lstnew_delfront(t_new_list **list);
void		ft_lstnew_delback(t_new_list **list);
void		ft_show_lstnew(t_new_list *list);
char		**get_all_environment(void);
void		insert_data(t_data *data, char *command);
char		*get_env(char *env, t_data *data);
void		free_data(t_data *data);
int			len_matrix(char **matrix);
void		master(char *command, t_data *data);

char	*get_valid_path(t_new_list *aux, t_data *data);
char	*ft_charjoin(char *s1, char c);
char	*get_valid_path(t_new_list *aux, t_data *data);
bool	all_char_equal_char(char *str, char chr);
bool	valid_string_condition_for_redirection(char *str);
bool	condition_add_more_one(int i, char ***matrix);
void	ajust_all_position(char ***matrix);
void	insert_data(t_data *data, char *command);
void	free_all_data(t_data *data);

#endif