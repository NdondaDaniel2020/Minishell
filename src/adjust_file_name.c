/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_file_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*other_join(int i2, int len_m, char *join, char **new_content)
{
	char	*aux;

	if (new_content[i2][0] == '"' || new_content[i2][0] == '\'')
	{
		aux = ft_strtrim(new_content[i2], "'\"");
		join = ft_strjoin_free(join, aux);
		free(aux);
	}
	else if (ft_strchr(new_content[i2], '\\'))
	{
		aux = strdelchr(new_content[i2], '\\');
		join = ft_strjoin_free(join, aux);
		free(aux);
	}
	else
		join = ft_strjoin_free(join, new_content[i2]);
	if (i2 < len_m - 1)
		join = ft_strjoin_free(join, "/");
	return (join);
}

static char	*the_file_directory_is_validated(
		int len_m, bool *valid, char **new_content)
{
	int		i2;
	char	*join;

	i2 = 0;
	join = (char *)ft_calloc(1, sizeof(char));
	while (i2 < len_m)
	{
		if (i2 == len_m - 1 && (!is_directory_valid(join) || *valid == false)
			&& len_matrix(new_content) > 1)
		{
			join = ft_strjoin_free(join, new_content[i2]);
			ft_putstr_fd(join, 2);
			ft_putstr_fd(": No such file or directory", 2);
			return (free(join), NULL);
		}
		else
			join = other_join(i2, len_m, join, new_content);
		i2++;
	}
	return (join);
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
	(*valid) = ((count_chr(' ', new_content[i]) > 0
				&& count_chr('"', new_content[i]) > 0)
			|| (count_chr(' ', new_content[i]) > 0
				&& count_chr('\'', new_content[i]) > 0)
			|| (count_chr(' ', new_content[i]) > 0
				&& count_chr('\\', new_content[i])
				== count_chr(' ', new_content[i]))
			|| (count_chr(' ', new_content[i]) == 0));
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
			if (i == (len_m - 1) && condition_adjust(i, new_content))
				remove_excess(i, new_content);
			else
				set_value(i, &valid, new_content);
			i++;
		}
		join = the_file_directory_is_validated(len_m, &valid, new_content);
		if (valid == false && join == NULL)
			return (free_matrix(new_content), NULL);
	}
	return (free_matrix(new_content), join);
}
