#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <readline/history.h>
#include <readline/readline.h>

typedef struct s_data
{
	char	*output;
	char	*put_amb;
	char	**split_cmd;
}			t_data;

void	cd(t_data *data);
void	pwd(t_data *data);
void	echo(t_data *data);
void	exit_(t_data *data);

void	init_data(t_data *data);
void	free_matrix(char **matrix);
void	free_all_data(t_data *data);
char	*ft_charjoin_free(char *s1, char c);

#endif