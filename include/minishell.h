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
	char	*command;
	char	*output;
	char	*put_amb;
	t_btree	*btree;
}			t_data;

/*builtin*/
void	cd(t_data *data);
void	pwd(t_data *data);
void	echo(t_data *data);
void	exit_(t_data *data);


/*init and free*/
void	init_data(t_data *data);
void	free_matrix(char **matrix);
void	free_all_data(t_data *data);
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

#endif