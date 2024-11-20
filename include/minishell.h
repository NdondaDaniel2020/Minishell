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

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	char			**content;
	int				item;
}					t_btree;

typedef struct s_data
{
	bool	space;
	char	*command;
	char	*output;
	char	*put_amb;
	char	**path;
	char	**envp;
	t_btree	*btree;
}			t_data;

typedef struct s_valid
{
	bool	is_quota;
	bool	is_transition;
}			t_valid;

/*builtin*/
void	cd(t_data *data);
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
int		count_word(char **words);
void	init_valid(t_valid	*valid);
void	traverse_n(int *i, t_data *data);

int	put_environment(int i1, int i2, t_valid	*valid, t_data *data);
int	traverse_the_array(int i1, int i2, t_valid	*valid, t_data *data);
int	trasition_master_master(int i1, int i2, t_valid	*valid, t_data *data);


char	**concat_env(char **env1, char **env2);
char    **get_env_1(void);
char    **get_env_2(void);
void	env(t_data *data);

void	unset(t_data *data);
void	export(t_data *data);
void	other_command(t_data *data);

bool	check_error(int i1, t_btree *aux);
bool	print_export(t_data *data);
int		ft_strnchrcmp(const char *s1, const char *s2, size_t n, char chr);
void	add_environment_variable(char *env_var, t_data *data);

#endif