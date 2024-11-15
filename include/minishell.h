#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
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


/*btree*/
t_btree	*insert_into_btree(t_btree *root, int item, char *content);

t_btree	*remove_tree_trunk(t_btree *root, int item);
t_btree	*remove_tree_leaf(t_btree *root);
t_btree	*remove_tree(t_btree *root, int item);

t_btree	*remove_all_tree(t_btree *root);

int		search_btree(t_btree *root, int item);
void	show_btree(t_btree *root);
int		len_btree(t_btree *root);

int		count_word(char **words);
void	init_valid(t_valid	*valid);
void	traverse_n(int *i, t_data *data);

int	put_environment(int i1, int i2, t_valid	*valid, t_data *data);
int	traverse_the_array(int i1, int i2, t_valid	*valid, t_data *data);
int	trasition_master_master(int i1, int i2, t_valid	*valid, t_data *data);

#endif