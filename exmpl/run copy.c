
#include "run.h"

int	is_directory_valid(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

////////////////////////////////////////////////////////

bool	space_before_string(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == '\'') || (str[i] == '"'))
		i++;
	if (str[i] == ' ')
		return (true);
	return (false);
}

bool	space_after_string(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (len > 1 && ((str[len] == '\'') || (str[len] == '"')))
		len--;
	if (str[len] == ' ')
		return (true);
	return (false);
}

int	star_alpha(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == '\'') || (str[i] == '"'))
		i++;
	return (i);
}

bool	condition_adjust(int i, char **new_content)
{
	return ((count_chr('"', new_content[i]) > 0
					&& count_chr('\'', new_content[i]) > 0)
			|| (((count_chr('\'', new_content[i]) > 0
							&& count_chr('"', new_content[i]) == 0)
						|| (count_chr('"', new_content[i]) > 0
							&& count_chr('\'', new_content[i]) == 0))
					&& (space_before_string(new_content[i]) == false
						&& space_after_string(new_content[i]) == false))
			|| (count_chr('\'', new_content[i]) > 0
					&& count_chr('"', new_content[i]) == 0
					&& count_chr('\'', (new_content[i]
						+ star_alpha(new_content[i]))) % 2 != 0)
			|| (count_chr('"', new_content[i]) > 0
					&& count_chr('\'', new_content[i]) == 0
					&& count_chr('"', (new_content[i]
						+ star_alpha(new_content[i]))) % 2 != 0));
}

bool	condition_error_directory(int i, char **new_content)
{
	return (((count_chr('\'', new_content[i]) > 0
					&& count_chr('"', new_content[i]) == 0)
				|| (count_chr('"', new_content[i]) > 0
					&& count_chr('\'', new_content[i]) == 0))
			&& (space_before_string(new_content[i]) == true));
}

bool	condition_error_not_found(int i, char **new_content)
{
	return (((count_chr('\'', new_content[i]) > 0
					&& count_chr('"', new_content[i]) == 0)
				|| (count_chr('"', new_content[i]) > 0
					&& count_chr('\'', new_content[i]) == 0))
			&& (space_before_string(new_content[i]) == false
				&& space_after_string(new_content[i]) == true));
}

char	*the_file_directory_is_validated(int len_m, char **new_content)
{
	int		i2;
	char	*join;

	i2 = 0;
	join = (char *)ft_calloc(1, sizeof(char));
	while (i2 < len_m)
	{
		if (i2 == len_m - 1 && !is_directory_valid(join)
			&& len_matrix(new_content) > 1)
		{
			join = ft_strjoin_free(join, new_content[i2]);
			join = ft_strjoin_free(join, "/");
			ft_putstr_fd(join, 2);
			ft_putstr_fd(": No such file or directory", 2);
			return (free(join), NULL);
		}
		else
		{
			join = ft_strjoin_free(join, new_content[i2]);
			if (i2 < len_m - 1)
				join = ft_strjoin_free(join, "/");
		}
		i2++;
	}
	return (join);
}

static bool	show_error_is_directory(int len_m, char **new_content)
{
	int		i2;
	char	*join;

	if (len_m == 1)
		ft_putstr_fd(": No such file or directory", 2);
	else
	{
		i2 = 0;
		join = (char *)ft_calloc(1, sizeof(char));
		while (i2 < len_m - 1)
		{
			join = ft_strjoin_free(join, new_content[i2]);
			join = ft_strjoin_free(join, "/");
			i2++;
		}
		ft_putstr_fd(join, 2);
		ft_putstr_fd(": Is a directory", 2);
		free(join);
	}
	return (true);
}

static void	remove_excess(int i, char **new_content)
{
	char	*aux_content;

	if (new_content[i][0] == '\'')
		aux_content = ft_strtrim(new_content[i], "'");
	else
		aux_content = ft_strtrim(new_content[i], "\"");
	free(new_content[i]);
	new_content[i] = aux_content;
}

static void	set_value(int i, bool *valid, char **new_content)
{
	(*valid) = (count_chr(' ', new_content[i]) > 0
				&& count_chr('"', new_content[i]) > 0)
			|| (count_chr(' ', new_content[i]) > 0
				&& count_chr('\\', new_content[i])
				== count_chr(' ', new_content[i]))
			|| (count_chr(' ', new_content[i]) == 0);
}

static bool	operating_conditions(int i, int len_m, char **new_content)
{
	if (condition_adjust(i, new_content))
		remove_excess(i, new_content);
	else if (condition_error_directory(i, new_content)
		&& show_error_is_directory(len_m, new_content))
		return (true);
	else if (condition_error_not_found(i, new_content)
		&& ft_printf(": command not found", 2))
		return (true);
	return (false);
}

char	*adjust_file_name(char *content)
{
	int		i;
	int		len_m;
	bool	valid;
	char	*join;
	char	**new_content;

	valid = false;
	new_content = ft_split(content, '/');
	len_m = len_matrix(new_content);
	if (len_m > 0)
	{
		i = 0;
		while (new_content[i])
		{
			if (i == (len_m - 1) && operating_conditions(i, len_m, new_content))
				return (free_matrix(new_content), NULL);
			else
				set_value(i, &valid, new_content);
			i++;
		}
		join = the_file_directory_is_validated(len_m, new_content);
		if (!valid && join == NULL)
			return (free_matrix(new_content), NULL);
	}
    return (free_matrix(new_content), join);
}

int	main(void)
{
	char	*content;
	char	*new_content;

	content = ft_strdup("\"\"tes1.txt\"\"");
	new_content = adjust_file_name(content);
	ft_printf("%s\n", new_content);
	free(content);
	free(new_content);
    return (0);
}
