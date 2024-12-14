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
	while (str[pos])
	{
		if (str[pos] == '\'' || str[pos] == '"')
			i2 = false;
		pos--;
	}
	if (!i1 && !i2)
		return (false);
	return (true);
}

static char	**split_redirection_len_1(char *str, const char *chr)
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

static char	**split_redirection_len_2(char *str, const char *chr)
{
	int		len_n;
	char	**new_content;
	char	**aux_content;

	aux_content = ft_split(str, chr[0]);
	len_n = len_matrix(aux_content);
	int i = 0;
	while (aux_content[i])
	{
		ft_printf("[%s]\n", aux_content[i]);
		i++;
	}
	// new_content = (char **)ft_calloc(len_n + 2, sizeof(char *));

	// if (len_n == 1 && str[0] == '>')
	// {
	// 	new_content[0] = ft_strdup(">");
	// 	new_content[1] = ft_strdup(aux_content[0]);
	// }
	// else if (len_n == 1)
	// {
	// 	new_content[0] = ft_strdup(aux_content[0]);
	// 	new_content[1] = ft_strdup(">");
	// }
	// if (len_n == 2)
	// {
	// 	new_content[0] = ft_strdup(aux_content[0]);
	// 	new_content[1] = ft_strdup(">");
	// 	new_content[2] = ft_strdup(aux_content[1]);
	// }
	free_matrix(aux_content);
	return (new_content);
}

int main(void)
{
	int		pos;
	int		iter;
	int		len_m;
	bool	valid;
	char	**split_cont;
	char	**new_content;
	char	*matrix[] = {"echo", "TEST", "test>>", "file.txt", NULL};

	iter = 0;
	valid = false;
	split_cont = NULL;
	len_m = len_matrix(matrix);
	while (matrix[iter])
	{
		if ((ft_strncmp(matrix[iter], ">", 1) == 0 && ft_strlen(matrix[iter]) == 1)
		 || (ft_strncmp(matrix[iter], "<", 1) == 0 && ft_strlen(matrix[iter]) == 1)
		 || (ft_strncmp(matrix[iter], "<<", 2) == 0 && ft_strlen(matrix[iter]) == 2)
		 || (ft_strncmp(matrix[iter], ">>", 2) == 0 && ft_strlen(matrix[iter]) == 2))
		{
			valid = true;
			break ;
		}
		if (ft_strchr(matrix[iter], '>') && (count_chr('>', matrix[iter]) == 1) && check_valid_redirection(get_position_chr('>', matrix[iter]), matrix[iter]))
		{
			split_cont = split_redirection_len_1(matrix[iter], ">");
			break;
		}

		if ((ft_strchr(matrix[iter], '>') && (count_chr('>', matrix[iter]) == 1) && check_valid_redirection(get_position_chr('>', matrix[iter]), matrix[iter]))
		 || (ft_strchr(matrix[iter], '<') && (count_chr('<', matrix[iter]) == 1) && check_valid_redirection(get_position_chr('<', matrix[iter]), matrix[iter])))
		{
			ft_printf("(%i)\n", count_chr('>', matrix[iter]));
			ft_printf("(%i)\n", count_chr('<', matrix[iter]));
			if (ft_strchr(matrix[iter], '>'))
				split_cont = split_redirection_len_1(matrix[iter], ">");
			else
				split_cont = split_redirection_len_1(matrix[iter], "<");
			pos = iter;
			break;
		}
		else if ((count_chr('<', matrix[iter]) == 2 && check_valid_redirection(get_position_chr('<', matrix[iter]), matrix[iter]))
				|| (count_chr('>', matrix[iter]) == 2 && check_valid_redirection(get_position_chr('>', matrix[iter]), matrix[iter])))
		{
			
			// if (ft_strchr(matrix[iter], '>'))
			// 	split_cont = split_redirection_len_2(matrix[iter], ">");
			// else
			// 	split_cont = split_redirection_len_2(matrix[iter], "<");
			pos = iter;
			break;
		}



		iter++;
	}

	if (valid == false && split_cont)
	{
		iter = 0;
		int	i1 = 0;
		int	i2 = 0;

		new_content = (char **)ft_calloc(len_m + len_matrix(split_cont), sizeof(char *));
		while (matrix[i1] && iter < (len_m + len_matrix(split_cont)))
		{
			if (iter == pos)
			{
				while (split_cont[i2])
				{
					new_content[iter] = split_cont[i2];
					i2++;
					iter++;
				}
				i1++;
			}
			else
			{
				new_content[iter] = matrix[i1];
				iter++;
				i1++;
			}
		}

		iter = 0;
		while (new_content[iter])
		{
			ft_printf("[%s]", new_content[iter]);
			iter++;
		}
	}
	else
		ft_printf("valid\n");
    return 0;
}
