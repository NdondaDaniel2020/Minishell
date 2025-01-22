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

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>

extern int g_satatus;

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
	int			heredoc_line_delimited;
	int			write_pipe_operation;
	int			read_pipe_operation;
	int			cpy_read_pipe_operation;
	int			cpy_write_operation;
	int			cpy_read_operation;
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

typedef struct t_red_fd
{
	int	fd;
	int	status;
	int	first_fd;
	int fd_target;
}		t_red_fd;

/* builtin cd*/
int			cd(t_new_list *aux, t_data *data);
void		update_pwd(t_data *data);
void		update_oldwpd(t_data *data);
void		add_in_list(char *value_env, t_new_list *aux, t_data *data);

int			is_directory_valid(const char *path);

bool		add_expanded_variable(t_new_list *aux, t_data *data);
bool		check_many_arguments(t_new_list *aux);


/*builtin pwd*/
int			pwd(t_new_list *aux, t_data *data);


/*builtin echo*/
int			echo(t_new_list *aux, t_data *data);
void		add_bar_n(t_new_list *aux);
void		traverse_n(int *i, t_data *data);
bool		echo_is_empty(t_new_list *aux);
int			count_word(char **words);


/*builtin exit*/
void		exit_(t_new_list *aux, t_data *data);
void		free_data(t_data *data);
int			numeric_argument_required(char *str);
int			check_error_exit(int ex, t_new_list *aux);


/*builtin env*/
int			env(t_new_list *aux, t_data *data);

char		*get_env(char *env, t_data *data);
char		**get_all_environment(void);


/*builtin export*/
int			export(t_new_list *aux, t_data *data);
void		add_environment_variable(char *env_var, t_data *data);
int			change_environment_variables_question_mark(int value, t_data *data);

int			is_valid_char(char c);
int			ft_strnchrcmp(const char *s1, const char *s2, size_t n, char chr);

bool		print_export(t_data *data);
bool		check_error(int i1, t_new_list *aux);

char		*analize_env(char *env);


/*builtin unset*/
int			unset(t_data *data);
void		remove_env(int i1, char *env, t_data *data);


/*init and free*/
void		init_data(t_data *data);
void		free_matrix(char **matrix);
void		free_all_data(t_data *data);
void		*ft_realloc(void* ptr, size_t original_size, size_t new_size);

char		*ft_charjoin(char *s1, char c);
char		*ft_charjoin_free(char *s1, char c);


/* functions */
char		**split_2(char *str, char chr);

int			other_command(int i, t_new_list *aux, t_data *data);
char		*get_valid_path(t_new_list *aux, t_data *data);
void		insert_data(t_data *data, char *command);
t_index_str	*get_absolute_path(int i, t_new_list *aux, t_data *data);

int			list_builtins(char *command);
int			len_matrix(char **matrix);
int			get_last_position(t_new_list *aux);

bool		first_str(char chr, char *str);
int			count_chr(char chr, char *str);

int			get_position_chr(char chr, char *str);
bool		valid_string_condition_for_redirection(char *str);
void		ajust_all_position(char ***matrix);
char		**reset_the_array_for_redirection(char **matrix);

bool		first_str(char chr, char *str);
int			count_chr(char chr, char *str);
int			get_position_chr(char chr, char *str);
bool		check_valid_redirection(int pos, char *str);

/* redirecionamento */
void		redirection(t_new_list *aux, t_data *data);
int			is_redirection(char *str);
void		init_two_extract(t_two_extract *ext);
void		init_var_redirection(t_var_red *red);
void		init_extract(t_extract *extract);
int			ft_strnpos(const char *big, const char *little, size_t len);
char		**list_error(void);
int			count_extract_redirection(char chr, char *str);
t_extract	*extract_redirection_character(char chr, char *str);
t_extract	**extract_all_redirection_characters(char *str);

char		**reset_the_array_for_redirection(char **content);
void		free_extract_matrix(t_extract **matrix);
int			count_all_redirection(char *str);
int			str_in_list_redirection(char *str, int len_m);
int			pos_redirection(const char *big, const char *little, size_t len, int index);
void		free_indexing_matrix(t_index **indexed);
void		many_redirection(char *str, char **new_content, int *iter);
bool		str_in_matrix(char *str, char **matrix);
char		*substring(const char *str, int start, int end);
t_index		**indexing_matrix(int len, t_extract **matrix);


char		*adjust_file_name(char *content);
bool		space_before_string(char *str);
bool		space_after_string(char *str);
int			star_alpha(char *str);
bool		condition_adjust(int i, char **new_content);
char		*strdelchr(char *str, char chr);
bool		all_char_equal_char(char *str, char chr);
int			str_in_list_redirection(char *str, int len_m);

int			execute_command(int i, t_new_list *aux, t_data *data);
bool		valid_redirection_syntax(t_new_list *aux);
bool		adjust_filename_in_redirection_syntax(t_new_list *aux);
bool		simple_error(char *command);
void		matrix_space_position_adjustment(char ***matrix);

/* list */
t_new_list  *ft_lstnew_new(char **content);

void		ft_lstnew_addafter_pos(t_new_list **lst, t_new_list *ref, t_new_list *new);
void    	ft_lstnew_addback(t_new_list **lst, t_new_list *new);
void    	ft_lstnew_addfront(t_new_list **lst, t_new_list *new);
void		ft_lstnew_free(char **matrix, t_new_list *removed);
void		ft_lstnew_delfront(t_new_list **list);
void		ft_lstnew_delback(t_new_list **list);
void		ft_show_lstnew(t_new_list *list);
int     	ft_lstnew_size(t_new_list *lst);

/* rediction exec*/
void		output(t_data *data, t_new_list *aux);
void		input(t_data *data, t_new_list *aux);
void		output_append(t_data *data, t_new_list *aux);
void		setup_redir(int fd, int fd_target);
void		init_red_fd(t_red_fd *red_fd);

int			open_file(const char *file, int mode);
int			left_right_redirection(int i, t_data *data, int mode);
int			double_right_redirect(int i, t_data *data, int mode);
int			double_left_redirect(int i, t_data *data, t_red_fd *red_fd);
int			right_redirect(int i, t_data *data, int mode);
int			left_redirect(int i, t_data *data, int mode, t_red_fd *red_fd);
void		all_redirect_directions_are_handled_here(int i, t_red_fd *red_fd, t_data *data);
void		no_such_file_or_directory(int i, t_data *data);
void		redirect_main_execution(t_red_fd *red_fd, t_data *data, t_new_list *aux);

bool		is_other_file(char *str);
void		setup_signal(void);
void		heredoc(t_data *data, char *delimiter);
void		put_warning(int line, char *delimiter);
void		environment_variation_expansion_in_heredoc(char **line, t_data *data);
void		null_string(char ***matrix);

void		execute_commands_with_pipe(int value_redirection, t_data *data);
void		execute_commands_without_pipe(int value_redirection, t_data *data);

bool		heredoc_pipe_fork(t_data *data);

char		*exolate_the_content(char *str);
char		*extract_value_env_quotes(char *str, char *sub, t_data *data);
char		*exolate_the_content_with_double_quotes(char *str, t_data *data);
char		*extracting_the_value_with_single_quotes(char *str, t_data *data);
char		*get_environment_variation_expansion(char *str, t_data *data);
void		environment_variation_expansion(char ***matrix, t_data *data);

bool		all_is_space(char *str);
bool		is_pipe_heredoc(char *command);
bool		has_unclosed_quotes(const char *str);
char		character_of_unclosed_quotes(const char *str);

bool		heredoc_quotes(t_data *data, char **command);

#endif