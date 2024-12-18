/* ************************************************************************** */
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

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

int	len_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	count_chr(char chr, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == chr)
			count++;
		i++;
	}
	return (count);
}

int	get_position_chr(char chr, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == chr)
			return (i);
		i++;
	}
	return (-1);
}

static bool	check_valid_redirection(int pos, char *str)
{
	bool	i1;
	bool	i2;

	i1 = true;
	i2 = true;
	while (str[pos])
	{
		if (str[pos] == '\'' || str[pos] == '"')
			i1 = false;
		pos++;
	}
	pos--;
	while (pos > 0 && str[pos])
	{
		if (str[pos] == '\'' || str[pos] == '"')
			i2 = false;
		pos--;
	}
	if (!i1 && !i2)
		return (false);
	return (true);
}







static char	**split_redirection(char *str, const char *chr)
{
	int		len_n;
	char	**new_content;
	char	**aux_content;

	aux_content = ft_split(str, chr[0]);
	len_n = len_matrix(aux_content);
	new_content = (char **)ft_calloc(len_n + 2, sizeof(char *));
	if (len_n == 1 && str[0] == chr[0])
	{
		new_content[0] = ft_strdup(chr);
		new_content[1] = ft_strdup(aux_content[0]);
	}
	else if (len_n == 1)
	{
		new_content[0] = ft_strdup(aux_content[0]);
		new_content[1] = ft_strdup(chr);
	}
	if (len_n == 2)
	{
		new_content[0] = ft_strdup(aux_content[0]);
		new_content[1] = ft_strdup(chr);
		new_content[2] = ft_strdup(aux_content[1]);
	}
	free_matrix(aux_content);
	return (new_content);
}

bool	valid_string_condition_for_redirection(char *str)
{
	return ((ft_strncmp(str, ">", 1) == 0 && ft_strlen(str) == 1)
		 || (ft_strncmp(str, "<", 1) == 0 && ft_strlen(str) == 1)
		 || (ft_strncmp(str, "<<", 2) == 0 && ft_strlen(str) == 2)
		 || (ft_strncmp(str, ">>", 2) == 0 && ft_strlen(str) == 2));
}

static bool	invalid_string_condition_for_redirection(char *str)
{
	return ((count_chr('>', str) == 1) && (ft_strchr(str, '>')
				&& check_valid_redirection(get_position_chr('>', str), str))
		 || (count_chr('<', str) == 1) && (ft_strchr(str, '<')
		 		&& check_valid_redirection(get_position_chr('<', str), str))
		 || (count_chr('<', str) == 2
		 		&& check_valid_redirection(get_position_chr('<', str), str))
		 || (count_chr('>', str) == 2
		 		&& check_valid_redirection(get_position_chr('>', str), str)));
}

static char	**join_comands(int len_m, int pos, char **matrix, char **split_cont)
{
	int		i1 = 0;
	int		i2 = 0;
	int		iter = 0;
	char	**new_content;

	new_content = (char **)ft_calloc(len_m + len_matrix(split_cont), sizeof(char *));
	while (matrix[i1] && iter < (len_m + len_matrix(split_cont)))
	{
		if (iter == pos)
		{
			while (split_cont[i2])
				new_content[iter++] = split_cont[i2++];
			i1++;
		}
		else
			new_content[iter++] = ft_strdup(matrix[i1++]);
	}
	free(split_cont);
	return (new_content);
}

static bool	condition_redirection(bool *valid, char *str, char ***split_cont)
{
	if (valid_string_condition_for_redirection(str))
	{
		(*valid) = true;
		return (true);
	}
	if (invalid_string_condition_for_redirection(str))
	{
		if (ft_strchr(str, '>') && count_chr('>', str) == 2)
			(*split_cont) = split_redirection(str, ">>");
		else if (ft_strchr(str, '<') && count_chr('<', str) == 2)
			(*split_cont) = split_redirection(str, "<<");
		else if (ft_strchr(str, '>') && count_chr('>', str) == 1)
			(*split_cont) = split_redirection(str, ">");
		else if (ft_strchr(str, '<') && count_chr('<', str) == 1)
			(*split_cont) = split_redirection(str, "<");
		return (true);
	}
	return (false);
}

static void	change_position(int pos, int len, char ***matrix)
{
	char	**auxm;

	auxm = (char **)ft_calloc(3 , sizeof(char *));
	auxm[0] = (*matrix)[pos];
	auxm[1] = (*matrix)[pos + 1];
	while (pos < len - 2)
	{
		(*matrix)[pos] = (*matrix)[pos + 2];
		pos++;
	}
	(*matrix)[len - 2] = auxm[0];
	(*matrix)[len - 1] = auxm[1];
	free(auxm);
}

char	**ajust_position(char ***matrix)
{
	int		i;
	int		len;
	int		pos;

	i = 0;
	pos = -1;
	len = len_matrix((*matrix));
	while ((*matrix)[i])
	{
		if (valid_string_condition_for_redirection((*matrix)[i]))
		{
			pos = i;
			break ;
		}
		i++;
	}
    if (pos != -1 && pos < len - 1)
		change_position(pos, len, matrix);
	return ((*matrix));
}

char **reset_the_array_for_redirection(char **matrix)
{
    int		pos;
    int		iter;
    int		len_m;
    bool	valid;
    char	**split_cont;

    pos = -1;
    iter = 0;
    valid = false;
    split_cont = NULL;
    len_m = len_matrix(matrix);
    while (matrix[iter])
    {
        if (condition_redirection(&valid, matrix[iter], &split_cont))
        {
            pos = iter;
            break ;
        }
        iter++;
    }
    if (valid == false && split_cont)
		return (join_comands(len_m, pos, matrix, split_cont));
	return (NULL);
}

int main(void)
{
	int		i;
	char	**new_content;
	char	**matrix;

	i = 0;
	matrix = (char **)ft_calloc(9, sizeof(char *));
	matrix[0] = ft_strdup("echo");
	matrix[1] = ft_strdup("TEST");
	matrix[2] = ft_strdup("test>");
	matrix[3] = ft_strdup("file.txt");
	matrix[4] = ft_strdup("TEST");
	matrix[5] = ft_strdup(">>");
	matrix[6] = ft_strdup("TEST");
	matrix[7] = ft_strdup("TEST");

	new_content = reset_the_array_for_redirection(matrix);
	new_content = ajust_position(&new_content);
	if (new_content)
	{
		while (new_content[i])
		{
			ft_printf("%i - %s\n", i, new_content[i]);
			i++;
		}
		free_matrix(new_content);
	}
	free_matrix(matrix);
    return (0);
}
