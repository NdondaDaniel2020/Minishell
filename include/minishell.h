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
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>
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
	int			copy_fd;
	bool		is_pipe;
	bool		space;
	bool		automatic_input;
	char		*command;
	char		*output;
	char		*put_amb;
	char		**path;
	char		**envp;
	t_new_list	*list;
}			t_data;

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

/* builtin cd*/
void	cd(t_new_list *aux, t_data *data);
void	update_pwd(t_data *data);
void	update_oldwpd(t_data *data);
void	add_in_list(char *value_env, t_new_list *aux, t_data *data);

int		is_directory_valid(const char *path);

bool	add_expanded_variable(t_new_list *aux, t_data *data);
bool	check_many_arguments(t_new_list *aux, t_data *data);


/*builtin pwd*/
void	pwd(t_new_list *aux, t_data *data);


/*builtin echo*/
void	echo(t_new_list *aux, t_data *data);
void	init_valid(t_valid	*valid);
void	traverse_n(int *i, t_data *data);

int		count_word(char **words);
int		put_environment(int i1, int i2, t_valid	*valid, t_data *data);
int		traverse_the_array(int i1, int i2, t_valid	*valid, t_data *data);
int		trasition_master_master(int i1, int i2, t_valid	*valid, t_data *data);


/*builtin exit*/
void	exit_(t_new_list *aux, t_data *data);

bool	check_error_exit(int i, int *ex, t_new_list *aux);


/*builtin env*/
void	env(t_new_list *aux, t_data *data);

char	*get_env(char *env, t_data *data);
char	**get_all_environment(void);


/*builtin export*/
void	export(t_new_list *aux, t_data *data);
void	add_environment_variable(char *env_var, t_data *data);
void	change_environment_variables_question_mark(int value, t_data *data);

int		is_valid_char(char c);
int		ft_strnchrcmp(const char *s1, const char *s2, size_t n, char chr);

bool	print_export(t_data *data);
bool	check_error(int i1, t_new_list *aux);

char	*analize_env(char *env);


/*builtin unset*/
void	unset(t_data *data);
void	remove_env(int i1, char *env, t_data *data);


/*init and free*/
void	init_data(t_data *data);
void	free_matrix(char **matrix);
void	free_all_data(t_data *data);
void	*ft_realloc(void* ptr, size_t original_size, size_t new_size);

char	*ft_charjoin(char *s1, char c);
char	*ft_charjoin_free(char *s1, char c);


/* functions */
char	**split_2(char *str, char chr);
char	*get_valid_path(t_new_list *aux, t_data *data);

void	other_command(int i, t_new_list *aux, t_data *data);
void	insert_data(t_data *data, char *command);

int		list_builtins(char *command);
int		len_matrix(char **matrix);
int		get_last_position(t_new_list *aux);

bool	first_str(char chr, char *str);
int		count_chr(char chr, char *str);

void	check_environment_variable_expansion(t_new_list *aux, t_data *data);
bool	condition_extract_value_env_quotes(int i, t_new_list *aux);
void	extract_value_env_quotes(int i, t_new_list *aux, t_data *data);

bool	is_redirection(char *str);
int		get_position_chr(char chr, char *str);

/* list */
t_new_list  *ft_lstnew_new(char **content);

void    	ft_lstnew_addback(t_new_list **lst, t_new_list *new);
void    	ft_lstnew_addfront(t_new_list **lst, t_new_list *new);
void		ft_lstnew_free(char **matrix, t_new_list *removed);
void		ft_lstnew_delfront(t_new_list **list);
void		ft_lstnew_delback(t_new_list **list);
void		ft_show_lstnew(t_new_list *list);

int     	ft_lstnew_size(t_new_list *lst);

#endif