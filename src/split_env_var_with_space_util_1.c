/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_var_with_space_util_1.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_split_env(t_split_env *split_env)
{
	split_env->i1 = 0;
	split_env->i2 = 0;
	split_env->len = 0;
	split_env->start = 0;
	split_env->index = 0;
	split_env->break_point = 0;
	split_env->new_matrix = NULL;
}

static int	get_pos_break_position(char	*env_var_value, char *string,
	char *string_exp)
{
	int	value1;
	int	value2;
	int	value3;

	value1 = ft_strnpos2(string_exp, env_var_value, ft_strlen(string_exp));
	value2 = ft_strnpos2(string, env_var_value, ft_strlen(string_exp));
	if (value2 == value1)
	{
		value3 = ft_strnpos2(string_exp + (ft_strlen(env_var_value) - 1),
				env_var_value, ft_strlen(string_exp + (ft_strlen(
							env_var_value) - 1)));
		return ((ft_strlen(env_var_value) - 1) + value3);
	}
	return (value1);
}

int	get_break_position(t_index_str *str, char *string, char *string_exp,
	t_data *data)
{
	int		f;
	char	*env_var_value;

	env_var_value = get_env(str->str + 1, data);
	if (ft_strchr(env_var_value, ' '))
	{
		f = 0;
		while (env_var_value[f])
		{
			while (env_var_value[f] == ' ')
				f++;
			while (env_var_value[f] && env_var_value[f] != ' ')
				f++;
			if (env_var_value[f] == ' ')
			{
				if (str->index == 0)
					return (get_pos_break_position(env_var_value, string,
							string_exp) + f);
				str->index--;
			}
		}
	}
	return (-1);
}

char	**dup_matrix(char **matrix)
{
	int		i;
	int		len;
	char	**new_matrix;

	len = len_matrix(matrix);
	new_matrix = (char **)ft_calloc((len + 1), sizeof(char *));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_matrix[i] = strdup(matrix[i]);
		if (!new_matrix[i])
		{
			while (i > 0)
				free(new_matrix[--i]);
			free(new_matrix);
			return (NULL);
		}
		i++;
	}
	new_matrix[len] = NULL;
	return (new_matrix);
}

char	**all_adjustments_in_the_matrix(char ***matrix, t_data *data)
{
	char	**cpy_matrix;
	char	**new_matrix;

	matrix_space_position_adjustment(matrix);
	null_string(matrix);
	cpy_matrix = dup_matrix((*matrix));
	environment_variation_expansion(matrix, data);
	matrix_space_position_adjustment(&cpy_matrix);
	matrix_space_position_adjustment(matrix);
	new_matrix = split_env_var_with_space(cpy_matrix, (*matrix), data);
	return (new_matrix);
}
