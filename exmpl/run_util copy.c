#include "run.h"

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
char	**list_error(void)
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

int	get_value_erro(char *str, char *str_pos)
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
int	ft_strnpos(const char *big, const char *little, size_t len)
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

int	ft_strnpos(const char *big, const char *little, size_t len)
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
void	free_extract_matrix(t_extract **matrix)
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

static bool	redirection_is_string(int i1, t_var_red	*red, char *str)
{
	int	pos;

	pos = ft_strnpos(str, red->extract_matrix[i1]->string, ft_strlen(str));
	if (check_valid_redirection(pos, str) == false)
		return (true);
	return (false);
}

int	is_redirection(char *str)
{
	int			i1;
	int			i2;
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
			if (redirection_is_string(i1, &red, str))
				return (0);
			if (check_redirection_error(i1, i2, &red, str))
				return (2);
			i2++;
		}
		i1++;
	}
	free_extract_matrix(red.extract_matrix);
	return (1);
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void	init_index(t_index *index)
{
	index->index = 0;
	index->content = NULL;
}

int	count_all_redirection(char *str)
{
	int			i;
	t_extract	**matrix;

	i = 0;
	matrix = extract_all_redirection_characters(str);
	while (matrix[i])
		i++;
	free_extract_matrix(matrix);
	return (i);
}

int	str_in_list_redirection(char *str, int len_m)
{
	int			i;
	int			len;
	int			pos;
	static char	*list[] = {"<>", ">>", "<<","<", ">", NULL};

	i = 0;
	len = ft_strlen(str);
	while (list[i])
	{
		pos = ft_strnpos(str, list[i], ft_strlen(str));
		if (ft_strncmp(str + pos, list[i], ft_strlen(list[i])) == 0)
		{
			if (pos != 0 && ((pos + 1 < len && str[pos + 1] != list[i][0])
				|| ((pos + 1 < len && str[pos + 1] == list[i][0])
				&& (pos + 2 < len && str[pos + 2] != list[i][0]))))
				return (len_m + (count_all_redirection(str) * 2) + 1);
			if ((pos == 0 && ((pos + 1 < len && str[pos + 1] != list[i][0])
				|| ((pos + 1 < len && str[pos + 1] == list[i][0])
				&& (pos + 2 < len && str[pos + 2] != list[i][0])))) || pos != 0)
				return (len_m + (count_all_redirection(str) * 2) + 1);
		}
		i++;
	}
	return (len_m);
}

bool	str_in_matrix(char *str, char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (ft_strncmp(str, matrix[i], ft_strlen(matrix[i])) == 0)
			return (true);
		i++;
	}
	return (false);
}

///
static bool	return_pos(int c, int n, int l_lit)
{
	if (c == l_lit)
	{
		n--;
		if (n == 0)
			return (true);
	}
	return (false);
}

void free_indexing_matrix(t_index **indexed)
{
    int i = 0;

    if (!indexed)
        return;

    while (indexed[i])
    {
        if (indexed[i]->content)
        {
            free(indexed[i]->content->string);
            free(indexed[i]->content);
        }
        free(indexed[i]);
        i++;
    }
    free(indexed);
}

/////////////
static bool release_in_case_of_error(int i, t_index **indexed)
{
	if (!indexed[i])
	{
		while (i-- > 0)
		{
			free(indexed[i]->content->string);
			free(indexed[i]->content);
			free(indexed[i]);
		}
		free(indexed);
		return (true);
	}
	return (false);
}

static int	get_value_index(int i, t_extract **matrix)
{
	if (ft_strncmp(matrix[i]->string, "<>", 2) == 0)
		return (0);
	else if (ft_strncmp(matrix[i]->string, ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(matrix[i]->string, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(matrix[i]->string, ">", 1) == 0)
		return (3);
	else if (ft_strncmp(matrix[i]->string, "<", 1) == 0)
		return (4);
}

t_index	**indexing_matrix(int len, t_extract **matrix)
{
	int		i;
	int		vidx;
	int		index[5];
	t_index	**indexed;

	i = 0;
	vidx = 0;
	while (vidx < 5)
		index[vidx++] = 0;
	indexed = (t_index **)ft_calloc(len + 1, sizeof(t_index *));
	if (!indexed)
		return (NULL);
	while (matrix[i])
	{
		indexed[i] = (t_index *)ft_calloc(1, sizeof(t_index));
		if (release_in_case_of_error(i, indexed))
			return (NULL);
		vidx = get_value_index(i, matrix);
		index[vidx]++;
		indexed[i]->index = index[vidx];
		indexed[i]->content = matrix[i];
		i++;
	}
	free(matrix);
	return (indexed);
}

/////////////

int	pos_redirection(const char *big, const char *little, size_t len, int index)
{
	size_t	i;
	size_t	l_lit;

	i = 0;
	l_lit = ft_strlen(little);
	if ((len == 0 && !little) || big == little || l_lit == 0)
		return (-1);
	while (i < len)
	{
		if (l_lit == 1 && big[i] == little[0]
			&& (big[i - 1] != '>' && big[i - 1] != '<')
			&& (big[i + 1] != '>' && big[i + 1] != '<') && --index == 0)
			return (i);
		else if (l_lit == 2 && big[i] == little[0] && big[i + 1] == little[1]
			&& (big[i - 1] != '>' && big[i - 1] != '<')
			&& (big[i + 2] != '>' && big[i + 2] != '<') && --index == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*substring(const char *str, int start, int end)
{
	int 	len;
	char	*sub;

	len = strlen(str);
	if (start > end)
		return (NULL);
	if (start < 0)
		start = 0;
	if (end > len)
		end = len;
	sub = (char *)malloc((end - start + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, str + start, end - start + 1);
	sub[end - start] = '\0';
	return (sub);
}

/////////////
static int	firts_str(int i, char *str, char **new_content, t_index **indexsing)
{
	int	pos;
	int	start;

	start = len_matrix(new_content);
	pos = pos_redirection(str, indexsing[i]->content->string,
		ft_strlen(str), indexsing[i]->index);
	if (pos != 0)
	{
		new_content[start++] = substring(str, 0, pos);
		new_content[start++] = ft_strdup(indexsing[i]->content->string);
		return (2);
	}
	else
	{
		new_content[start++] = ft_strdup(indexsing[i]->content->string);
		return (1);
	}
}

static int	other_str(int i, char *str, char **new_content, t_index **indexsing)
{
	int	pos1;
	int	pos2;
	int	start;

	start = len_matrix(new_content);
	pos1 = pos_redirection(str, indexsing[i - 1]->content->string,
		ft_strlen(str), indexsing[i - 1]->index);
	pos2 = pos_redirection(str, indexsing[i]->content->string,
		ft_strlen(str), indexsing[i]->index);
	new_content[start++] = substring(str, pos1 +
		ft_strlen(indexsing[i - 1]->content->string), pos2);
	new_content[start++] = ft_strdup(indexsing[i]->content->string);
	return (2);
}

static int	last_str(int i, char *str, char **new_content, t_index **indexsing)
{
	int	pos;
	int	start;

	start = len_matrix(new_content);
	pos = pos_redirection(str, indexsing[i - 1]->content->string,
		ft_strlen(str), indexsing[i - 1]->index);
	if ((pos + ft_strlen(indexsing[i - 1]->content->string)) < ft_strlen(str))
	{
		new_content[start++] = substring(str, pos +
			ft_strlen(indexsing[i - 1]->content->string), ft_strlen(str));
		return (1);
	}
	return (0);
}

void	many_redirection(char *str, char **new_content, int *iter)
{
	int		i;
	int		len_m;
	t_index	**indexsing;

	i = 0;
	len_m = count_all_redirection(str);
	indexsing = indexing_matrix(len_m,
		extract_all_redirection_characters(str));
	while (i < len_m)
	{
		if (i == 0)
			(*iter) += firts_str(i, str, new_content, indexsing);
		else
			(*iter) += other_str(i, str, new_content, indexsing);
		i++;
	}
	(*iter) += last_str(i, str, new_content, indexsing);
	free_indexing_matrix(indexsing);
}
/////////////

/////////////
