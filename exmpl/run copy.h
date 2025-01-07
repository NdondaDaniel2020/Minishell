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

void		init_index(t_index *index);
void		free_matrix(char **matrix);
int			len_matrix(char **matrix);
int			get_position_chr(char chr, char *str);
bool		check_valid_redirection(int pos, char *str);
void		init_two_extract(t_two_extract *ext);
void		init_var_redirection(t_var_red *red);
void		init_extract(t_extract *extract);
bool		first_str(char chr, char *str);
int			count_chr(char chr, char *str);
t_extract	*extract_redirection_character(char chr, char *str);
int			count_extract_redirection(char chr, char *str);
t_extract	**extract_all_redirection_characters(char *str);
char		**list_error(void);
int			get_value_erro(char *str, char *str_pos);
int			ft_strnpos(const char *big, const char *little, size_t len);
void		free_extract_matrix(t_extract **matrix);
int			is_redirection(char *str);


////////////////////////////////////////////////////////////////////////
int			count_all_redirection(char *str);
int			str_in_list_redirection(char *str, int len_m);
int			pos_redirection(const char *big, const char *little, size_t len, int index);
void		free_indexing_matrix(t_index **indexed);
void		many_redirection(char *str, char **new_content, int *iter);
char		*substring(const char *str, int start, int end);
t_index		**indexing_matrix(int len, t_extract **matrix);
char	**reset_the_array_for_redirection(char **content);
int		new_repartision(int iter, char *str, char **new_content);

#endif