/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_var_with_space.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_len_break_position(char **matrix, char **matrix_exp,
	t_split_env *s_e, t_data *data)
{
	s_e->index = 0;
	s_e->break_point = 0;
	while (s_e->break_point != -1)
	{
		s_e->break_point = get_the_string_break_position(s_e->index,
				matrix[s_e->i1], matrix_exp[s_e->i1], data);
		if (s_e->index == 0 && s_e->break_point == -1)
		{
			s_e->i2++;
			s_e->i1++;
		}
		else
		{
			if (s_e->break_point == -1)
			{
				s_e->i2++;
				s_e->i1++;
			}
			else
				s_e->i2++;
		}
		s_e->index++;
	}
}

int	len_env_var_with_space(char **matrix, char **matrix_exp, t_data *data)
{
	int			i;
	t_split_env	*s_e;

	s_e = (t_split_env *)ft_calloc(1, sizeof(t_split_env));
	init_split_env(s_e);
	while (matrix[s_e->i1])
	{
		if (ft_strchr(matrix[s_e->i1], '$'))
			get_len_break_position(matrix, matrix_exp, s_e, data);
		else
		{
			s_e->i2++;
			s_e->i1++;
		}
	}
	i = s_e->i2;
	free(s_e);
	return (i);
}

static void	split_env_var_in_space(char **matrix_exp, t_split_env *s_e)
{
	while (matrix_exp[s_e->i1][s_e->start] == ' ')
		s_e->start++;
	if (s_e->break_point == -1)
	{
		s_e->new_matrix[s_e->i2] = substring(matrix_exp[s_e->i1], s_e->start,
				ft_strlen(matrix_exp[s_e->i1]));
		s_e->i1++;
		s_e->i2++;
	}
	else
	{
		s_e->new_matrix[s_e->i2++] = substring(matrix_exp[s_e->i1], s_e->start,
				s_e->break_point);
		s_e->start = s_e->break_point;
	}
}

static void	env_var_with_space(char **matrix, char **matrix_exp,
	t_split_env *s_e, t_data *data)
{
	s_e->index = 0;
	s_e->start = 0;
	s_e->break_point = 0;
	while (s_e->break_point != -1)
	{
		s_e->break_point = get_the_string_break_position(s_e->index,
				matrix[s_e->i1], matrix_exp[s_e->i1], data);
		if (s_e->index == 0 && s_e->break_point == -1)
		{
			s_e->new_matrix[s_e->i2++] = ft_strdup(matrix_exp[s_e->i1++]);
			break ;
		}
		else
			split_env_var_in_space(matrix_exp, s_e);
		s_e->index++;
	}
}

char	**split_env_var_with_space(char **matrix, char **matrix_exp,
	t_data *data)
{
	t_split_env	*s_e;
	char		**new_matrix;

	s_e = (t_split_env *)ft_calloc(1, sizeof(t_split_env));
	init_split_env(s_e);
	s_e->len = len_env_var_with_space(matrix, matrix_exp, data);
	s_e->new_matrix = (char **)ft_calloc(s_e->len + 1, sizeof(char *));
	while (matrix[s_e->i1])
	{
		if (ft_strchr(matrix[s_e->i1], '$'))
			env_var_with_space(matrix, matrix_exp, s_e, data);
		else
			s_e->new_matrix[s_e->i2++] = ft_strdup(matrix_exp[s_e->i1++]);
	}
	new_matrix = s_e->new_matrix;
	free_matrix(matrix_exp);
	free_matrix(matrix);
	free(s_e);
	return (new_matrix);
}
