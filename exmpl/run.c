/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:26 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/09 12:04:37 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

bool	condition_put_env_quotes(char *str, char *sub) // """$USER"""
{
	return (first_str('\'', str) && (count_chr('\'', sub) % 2 != 0)
		&& (count_chr('"', sub) > 0));
}

bool	condition_extract_value_env_quotes(char *str, char *sub) // '''name'''
{
	return (first_str('"', str) && (count_chr('"', sub) % 2 != 0)
		&& (count_chr('\'', sub) > 0));
}

bool	condition_put_env(char *str, char *sub) // $USER
{
	return ((count_chr('"', str) == 0 && (count_chr('\'', sub) % 2 != 0))
		 || (first_str('"', str) && (count_chr('"', sub) % 2 == 0)
		 		&& (count_chr('\'', sub) > 0)));
}

bool	condition_extract_value_env(char *str, char *sub) // name
{
	return ((count_chr('"', sub) == 0 && count_chr('\'', sub) == 0)
		 || (count_chr('\'', sub) == 0 && (count_chr('"', sub) > 0))
		 || (count_chr('"', sub) == 0 && (count_chr('\'', sub) % 2 == 0))
		 || (first_str('\'', str) && (count_chr('\'', sub) % 2 == 0)
		 	&& (count_chr('"', sub) > 0)));
}

static void	extract_value_env(int i, t_new_list *aux, t_data *data)
{
	char	*value_env;
	char	*aux_env;

	aux_env = ft_strtrim(aux->content[0] + i, "\"'");
	value_env = get_env(aux_env + 1, data);
	// so add value_env in matrix os comportamentos abaaixo o codigo resolve

	free(aux_env);
}

void	extract_value_env_quotes(int i, char *str, t_data *data)
{
	char	*value_env;
	char	*aux_env;
	char	*mark;
	char	*cpy_env;

	aux_env = ft_strtrim(str, "\"'");
	value_env = get_env(aux_env + 1, data);
	if (value_env)
	{
		cpy_env = ft_strdup(value_env);
		mark = ft_strtrim(str + (i + ft_strlen(aux_env)), "\"");
		value_env = ft_strjoin(mark, value_env);
		value_env = ft_strjoin_free(value_env, mark);
		ft_printf("%s\n", value_env);
		// so add value_env in matrix os comportamentos abaaixo o codigo resolve
	}
	free(value_env);
	free(aux_env);
	free(cpy_env);
	free(mark);	
}

// void	check_environment_variable_expansion(char **str, t_data *data)

void	environment_variation_expansion(int i, char ***matrix, t_data *data)
{
	int 	ii;
	char	*sub;
	char	*value_env;

	ii = 0;
	while ((*matrix)[i][ii] && (*matrix)[i][ii] != '$')
		ii++;

	sub = ft_substr((*matrix)[i], 0, ft_strchr((*matrix)[i], '$') - (*matrix)[i]);
	if (condition_put_env((*matrix)[i], sub))
	{	
		int	old_size;
		int	new_size;

		value_env = ft_strtrim((*matrix)[i], "'\"");
		ft_printf("[%s]\n", value_env);

		old_size = ft_strlen((*matrix)[i]);
		new_size = ft_strlen(value_env);
		(*matrix)[i] = ft_realloc((*matrix)[i], old_size, new_size);
		ft_strlcpy((*matrix)[i], value_env, new_size);
		free(value_env);
	}
	else if (condition_extract_value_env((*matrix)[i], sub)) // V/
	{
		int 	pos;
		char	*aux;
		int		old_size;
		int		new_size;

		value_env = ft_strtrim((*matrix)[i], "'\"");
		pos = 0;
		while (value_env[pos] && value_env[pos] == '$')
			pos++;
		aux = get_env(value_env + pos, data);
		old_size = ft_strlen((*matrix)[i]);
		new_size = ft_strlen(aux);
		(*matrix)[i] = ft_realloc((*matrix)[i], old_size, new_size);
		ft_strlcpy((*matrix)[i], aux, new_size);
		free(value_env);
	}
	else if (condition_extract_value_env_quotes((*matrix)[i], sub))
	{	
		// ft_printf("'''name'''\n");
		// extract_value_env_quotes(i, (*matrix)[i], data);
	}	
	else if (condition_put_env_quotes((*matrix)[i], sub))
	{
		int	old_size;
		int	new_size;

		value_env = ft_strtrim((*matrix)[i], "'");
		ft_printf("[%s]\n", value_env);

		old_size = ft_strlen((*matrix)[i]);
		new_size = ft_strlen(value_env);
		(*matrix)[i] = ft_realloc((*matrix)[i], old_size, new_size);
		ft_strlcpy((*matrix)[i], value_env, new_size);
		free(value_env);
	}
	free(sub);
}

int	main(void)
{
	int		i;
	t_data	data;
	char	**matrix;

	i = 0;
	init_data(&data);
	data.envp = get_all_environment();
	matrix = split_2("echo:$USER", ':'); // ''$HOME''''$HOME''
	while (matrix[i])
	{
		ft_printf("%s\n", matrix[i]);
		if (ft_strchr(matrix[i], '$'))
			environment_variation_expansion(i, &matrix, &data);
		// ft_printf("%s\n", matrix[i]);
		i++;
	}
	free_matrix(matrix);
	free_data(&data);
	return (0);
}
