
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

void	init_two_extract(t_two_extract *ext)
{
	ext->len_1 = 0;
	ext->len_2 = 0;
	ext->ext1 = NULL;
	ext->ext2 = NULL;
}

void	init_var_redirection(t_var_red *red)
{
	red->list_error = NULL;
	red->extract_matrix = NULL;
}

void	init_extract(t_extract *extract)
{
	extract->string = NULL;
	extract->start = 0;
	extract->end = 0;
	extract->returned = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////



bool	first_str(char chr, char *str)
{
	if (str[0] == chr)
		return (true);
	return (false);
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

bool	check_valid_redirection(int pos, char *str)
{
	bool	i1;
	bool	i2;
	int		aux_value;

	i1 = true;
	i2 = true;
	aux_value = pos;
	while (str[pos])
	{
		if (str[pos] == '\'' || str[pos] == '"')
			i1 = false;
		pos++;
	}
	pos = aux_value;
	while (str[pos])
	{
		if (str[pos] == '\'' || str[pos] == '"')
			i2 = false;
		pos--;
	}
	if (i1 == false && i2 == false)
		return (false);
	return (true);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////

t_extract	*extract_redirection_character(char chr, char *str)
{
	int			pos;
	char		*str_strim;
	t_extract	*ext;

	ext = (t_extract *)ft_calloc(1, sizeof(t_extract));
	init_extract(ext);
	pos = get_position_chr(chr, str);
	if (pos == -1)
	{
		free(ext);
		return ((t_extract *)NULL);
	}
	while ((str[pos + ext->end] == ' ') || (str[pos + ext->end] == '>')
		|| (str[pos + ext->end] == '<'))
		ext->end++;
	str_strim = ft_substr(str, pos, ext->end);
	ext->string = ft_strtrim(str_strim, " ");
	ext->start = pos;
	ext->returned = pos + ext->end;
	free(str_strim);
	return (ext);
}

int	count_extract_redirection(char chr, char *str)
{
	int			i;
	int			end;
	int			len;
	t_extract	*ext;

	i = 0;
	end = 0;
	len = ft_strlen(str);
	while (end < len)
	{
		ext = extract_redirection_character(chr, str + end);
		if (ext == NULL)
			break;
		end += ext->returned;
		free(ext->string);
		free(ext);
		i++;
	}
	return (i);
}

/////
static bool	check_extract_lens(t_two_extract *ext, char *str)
{
	init_two_extract(ext);
	ext->len_1 = count_extract_redirection('>', str);
	ext->len_2 = count_extract_redirection('<', str);
	if (ext->len_1 == 0 && ext->len_2 == 0)
		return (true);
	return (false);
}

static void	two_extract(int i, int *end, t_extract **mtx, t_two_extract *ext)
{
	if (ext->ext1->start < ext->ext2->start)
	{
		mtx[i] = ext->ext1;
		(*end) += ext->ext1->returned;
		free(ext->ext2->string);
		free(ext->ext2);
	}
	else
	{
		mtx[i] = ext->ext2;
		(*end) += ext->ext2->returned;
		free(ext->ext1->string);
		free(ext->ext1);
	}
}

static void	extract_redir(int i, int *end, t_extract **mtx, t_two_extract *ext)
{
	if (ext->ext1 && ext->ext1->returned > 0 && ext->ext2 == NULL)
	{
		mtx[i] = ext->ext1;
		(*end) += ext->ext1->returned;
	}
	else if (ext->ext2 && ext->ext2->returned > 0 && ext->ext1 == NULL)
	{
		mtx[i] = ext->ext2;
		(*end) += ext->ext2->returned;
	}
	else if (ext->ext1 && ext->ext2 && ext->ext1->returned > 0
			&& ext->ext2->returned > 0)
		two_extract(i, end, mtx, ext);
}

t_extract	**extract_all_redirection_characters(char *str)
{
	int				i;
	int				end;
	t_two_extract	ext;
	t_extract		**matrix_ext;

	i = 0;
	end = 0;
	if (check_extract_lens(&ext, str))
		return ((t_extract **)(NULL));
	matrix_ext = (t_extract **)ft_calloc(ext.len_1 + ext.len_2 + 1,
		sizeof(t_extract *));
	if (!matrix_ext)
		return ((t_extract **)(NULL));
	while (i < (ext.len_1 + ext.len_2))
	{
		ext.ext1 = extract_redirection_character('>', str + end);
		ext.ext2 = extract_redirection_character('<', str + end);
		if (ext.ext1 == NULL && ext.ext2 == NULL)
			break ;
		extract_redir(i, &end, matrix_ext, &ext);
		i++;
	}
	return (matrix_ext);
}
/////
////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////
static char	**list_error(void)
{
	static char	*list[] = {"><", ">>>", "<<<", ">><", "<<>",
							"<>>", "<><", ">> ", "<< ", "<> ",
							"< ", "> ", NULL};

	return (list);
}
///////////

///////////
static int	adjust_value_error(int i, char *str_pos)
{
	while (str_pos[i] == ' ')
		i++;
	return (i);
}

static int	get_value_erro(char *str, char *str_pos)
{
	if (ft_strncmp(str, list_error()[0], ft_strlen(list_error()[0])) == 0)
		return (1);
	if ((ft_strncmp(str, list_error()[1], ft_strlen(list_error()[1])) == 0)
		|| (ft_strncmp(str, list_error()[2], ft_strlen(list_error()[2])) == 0)
		|| (ft_strncmp(str, list_error()[3], ft_strlen(list_error()[3])) == 0)
		|| (ft_strncmp(str, list_error()[4], ft_strlen(list_error()[4])) == 0)
		|| (ft_strncmp(str, list_error()[5], ft_strlen(list_error()[5])) == 0)
		|| (ft_strncmp(str, list_error()[6], ft_strlen(list_error()[6])) == 0))
		return (2);
	if ((ft_strncmp(str, list_error()[7], ft_strlen(list_error()[7])) == 0)
		|| (ft_strncmp(str, list_error()[8], ft_strlen(list_error()[8])) == 0)
		|| (ft_strncmp(str, list_error()[9], ft_strlen(list_error()[9])) == 0))
		return (adjust_value_error(3, str_pos));
	if ((ft_strncmp(str, list_error()[10], ft_strlen(list_error()[10])) == 0) ||
		(ft_strncmp(str, list_error()[11], ft_strlen(list_error()[11])) == 0))
		return (adjust_value_error(2, str_pos));
	return (0);
}
///////////

///////////
static int	ft_strnpos(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	l_lit;

	i = 0;
	l_lit = ft_strlen(little);
	if (len == 0 && !little)
		return (0);
	if (big == little || l_lit == 0)
		return (0);
	while (*big && i < len)
	{
		c = 0;
		if (*big == little[0])
		{
			while (little[c] == big[c] && little[c] && big[c] && i + c < len)
				c++;
		}
		if (c == l_lit)
			return (i);
		++big;
		i++;
	}
	return (0);
}
///////////

///////////
static void	free_extract_matrix(t_extract **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]->string);
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
///////////

//////////
static bool	check_redirection_error(int i1, int i2, t_var_red *red, char *str)
{
	int	pos;

	if (ft_strncmp(red->extract_matrix[i1]->string, red->list_error[i2],
		ft_strlen(red->list_error[i2])) == 0)
	{
		pos = ft_strnpos(str, red->extract_matrix[i1]->string, ft_strlen(str));
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(str[pos + get_value_erro(red->list_error[i2],
			 str + pos)], 2);
		ft_putstr_fd("'\n", 2);
		free_extract_matrix(red->extract_matrix);
		return (true);
	}
	return (false);
}

int	is_redirection(char *str)
{
	int			i1;
	int			i2;
	int			pos;
	t_var_red	red;

	if (str == NULL || (count_chr('<', str) == 0 && count_chr('>', str) == 0))
		return (0);
	i1 = 0;
	init_var_redirection(&red);
	red.list_error = list_error();
	red.extract_matrix = extract_all_redirection_characters(str);
	while (red.extract_matrix[i1])
	{
		i2 = 0;
		while (red.list_error[i2])
		{
			if (check_redirection_error(i1, i2, &red, str))
				return (2);
			i2++;
		}
		i1++;
	}
	free_extract_matrix(red.extract_matrix);
	return (1);
}
//////////

int main(void)
{
	char		str[] = "echo TEST >  > file.txt";

	is_redirection(str);
	return 0;
}