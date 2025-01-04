
#include "run.h"

/////////////

static bool	condition_extract(int i, int pos, char *str, char **list)
{
	int	len;

	len = ft_strlen(str);
	return ((pos != 0 && ((pos + 1 < len && str[pos + 1] != list[i][0])
					|| ((pos + 1 < len && str[pos + 1] == list[i][0])
					&& (pos + 2 < len && str[pos + 2] != list[i][0]))))
			|| (pos == 0 && ((pos + 1 < len && str[pos + 1] != list[i][0])
					|| ((pos + 1 < len && str[pos + 1] == list[i][0])
					&& (pos + 2 < len && str[pos + 2] != list[i][0]))))
			|| (pos != 0));
}

bool	valid_string_condition_for_redirection(char *str)
{
	return ((ft_strncmp(str, ">", 1) == 0 && ft_strlen(str) == 1)
		|| (ft_strncmp(str, "<", 1) == 0 && ft_strlen(str) == 1)
		|| (ft_strncmp(str, "<<", 2) == 0 && ft_strlen(str) == 2)
		|| (ft_strncmp(str, ">>", 2) == 0 && ft_strlen(str) == 2));
}

static bool	condition_to_add(char *str, bool added)
{
	return (added == false
		&& (valid_string_condition_for_redirection(str)
			|| (count_extract_redirection('<', str) == 0
			&& count_extract_redirection('>', str) == 0)));
}

int	new_repartision(int iter, char *str, char **new_content)
{
	int			i;
	int			pos;
	bool		added;
	static char	*list[] = {"<>", ">>", "<<","<", ">", NULL};

	i = 0;
	added = false;
	while (list[i])
	{
		pos = ft_strnpos(str, list[i], ft_strlen(str));
		if (ft_strncmp(str + pos, list[i], ft_strlen(list[i])) == 0
			&& condition_extract(i, pos, str, list))
		{
			many_redirection(str, new_content, &iter);
			break ;
		}
		else if (condition_to_add(str, added))
		{
			new_content[iter++] = ft_strdup(str);
			added = true;
			break ;
		}
		i++;
	}
	return (iter);
}

////////////////////////////////////////////////////////////////////////
char	**reset_the_array_for_redirection(char **content)
{
	int		i;
	int		iter;
	int		len_m;
	char	**new_content;

	i = 0;
	len_m = 0;
	len_m = len_matrix(content);
	while (content[i])
	{
		len_m = str_in_list_redirection(content[i], len_m);
		i++;
	}
	if (len_matrix(content) == len_m)
		return (NULL);
	new_content = (char **)ft_calloc(len_m + 1, sizeof(char *));
	i = 0;
	iter = 0;
	while (content[i])
	{
		iter = new_repartision(iter, content[i], new_content);
		i++;
	}
	return (new_content);
}

int main(void)
{
	int		i;
	char	**new_content;
	char	**content;

	content = (char **)ft_calloc(9, sizeof(char *));
	content[0] = ft_strdup(">>");
	content[1] = ft_strdup("test1");
	content[2] = ft_strdup(">>");
	content[3] = ft_strdup("test2>test3>");

	new_content = reset_the_array_for_redirection(content);
	if (new_content)
	{
		i = 0;
		while (new_content[i])
		{
			ft_printf("%s\n", new_content[i]);
			i++;
		}
		free_matrix(new_content);
	}
	free_matrix(content);
    return (0);
}
