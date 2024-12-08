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

/////////////////////////// STRUCTURES /////////////////////////////
typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	char			**content;
	int				item;
}					t_btree;
/////////////////////////// STRUCTURES /////////////////////////////

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
	
	t_btree		*btree;
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

/*builtin*/
void	cd(t_new_list *aux, t_data *data);
void	pwd(t_data *data);
void	echo(t_data *data);
void	exit_(t_data *data);


/*init and free*/
void	init_data(t_data *data);
void	free_matrix(char **matrix);
void	free_all_data(t_data *data);
char	*ft_charjoin(char *s1, char c);
char	*ft_charjoin_free(char *s1, char c);
void	*ft_realloc(void* ptr, size_t original_size, size_t new_size);

/*btree*/
t_btree	*insert_into_btree(t_btree *root, int item, char *content);

t_btree	*remove_tree_trunk(t_btree *root, int item);
t_btree	*remove_tree_leaf(t_btree *root);
t_btree	*remove_tree(t_btree *root, int item);
t_btree	*remove_all_tree(t_btree *root);

int		search_btree(t_btree *root, int item);
int		len_btree(t_btree *root);
void	show_btree(t_btree *root);


/* functions */
char	**split_2(char *str, char chr);

int		count_word(char **words);
void	init_valid(t_valid	*valid);
void	traverse_n(int *i, t_data *data);

int	put_environment(int i1, int i2, t_valid	*valid, t_data *data);
int	traverse_the_array(int i1, int i2, t_valid	*valid, t_data *data);
int	trasition_master_master(int i1, int i2, t_valid	*valid, t_data *data);

char	**get_all_environment(void);
void	env(t_new_list *aux, t_data *data);

void	unset(t_data *data);
void	export(t_data *data);
void	other_command(t_new_list *aux, t_data *data);

bool	check_error(int i1, t_new_list *aux);
bool	print_export(t_data *data);
int		ft_strnchrcmp(const char *s1, const char *s2, size_t n, char chr);
void	add_environment_variable(char *env_var, t_data *data);

char	*get_env(char *env, t_data *data);
void	change_environment_variables_question_mark(int value, t_data *data);
int		len_matrix(char **matrix);

char	*get_valid_path(t_new_list *aux, t_data *data);
void	insert_data(t_data *data, char *command);
int		list_builtins(char *command);
int		is_directory_valid(const char *path);

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