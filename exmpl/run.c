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

/* ajuste no caso especial de expancao $HOME == "ls -l" -> 'ls -l'*/

#include "run.h"

typedef struct s_split_env
{
	int		i1;
	int		i2;
	int		len;
	int		start;
	int		index;
	int		break_point;
	char	**new_matrix;
}			t_split_env;

////////////////////////////////////////////////////////////////////////////////

char	*ft_charjoin_free(char *s1, char c)
{
	char	*join;
	int		l1;
	int		i;

	if (!s1 && !c)
		return (NULL);
	i = 0;
	l1 = ft_strlen(s1);
	join = malloc((l1 + 2) * sizeof(char));
	if (!join)
		return (NULL);
	while (i < (l1 + 1))
	{
		if (i < l1)
			join[i] = s1[i];
		else
			join[i] = c;
		i++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
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

////////////////////////////////////////////////////////////////////////////////

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

static int	get_break_position(int *index, char *env_var, char *string_exp, t_data *data)
{
	int 	f;
	char	*env_var_value;

	env_var_value = get_env(env_var + 1, data);
	if (ft_strchr(env_var_value, ' '))
	{
		f = 0;
		while (env_var_value[f])
		{
			while (env_var_value[f] ==  ' ')
				f++;
			while (env_var_value[f] && env_var_value[f] != ' ')
				f++;
			if (env_var_value[f] ==  ' ')
			{
				if (*index == 0)
					return (ft_strnpos2(string_exp, env_var_value,
						ft_strlen(string_exp)) + f);
				(*index)--;
			}
		}
	}
	return (-1);
}

int	get_the_string_break_position(int index, char *string, char *string_exp, t_data *data)
{
	int		i;
	int		end;
	int		value;
	char	*env_var;

	i = 0;
	while (string[i])
	{
		if (string[i] == '$')
		{
			end = i + 1;
			while (ft_isalpha(string[end]) || string[end] == '_')
				end++;
			env_var = substring(string, i, end);
			value = get_break_position(&index, env_var, string_exp, data);
			if (value != -1)
				return (free(env_var), value);
			free(env_var);
			i = end - 1;
		}
		i++;
	}
	return (-1);
}

///
static void	get_len_break_position(char **matrix, char **matrix_exp, t_split_env *s_e, t_data *data)
{
	s_e->index = 0;
	s_e->break_point = 0;
	while (s_e->break_point != -1)
	{
		s_e->break_point = get_the_string_break_position(s_e->index,
			matrix[s_e->i1], matrix_exp[s_e->i1], data);
		if (s_e->index == 0 && s_e->break_point == -1)
			s_e->i2++, s_e->i1++;
		else
		{
			if (s_e->break_point == -1)
				s_e->i2++, s_e->i1++;
			else
				s_e->i2++;
		}
		s_e->index++;
	}
}

int	len_env_var_with_space(char **matrix, char **matrix_exp, t_data *data)
{
	int 		i;
	t_split_env	*s_e;

	s_e = (t_split_env *)ft_calloc(1, sizeof(t_split));
	init_split_env(s_e);
	while (matrix[s_e->i1])
	{
		if (ft_strchr(matrix[s_e->i1], '$'))
			get_len_break_position(matrix, matrix_exp, s_e, data);
		else
			s_e->i2++, s_e->i1++;
	}
	i = s_e->i2;
	free(s_e);
	return (i);
}
/////

/////
static void	split_env_var_in_space(char **matrix, char **matrix_exp, t_split_env *s_e, t_data *data)
{
	while (matrix_exp[s_e->i1][s_e->start] == ' ')
		s_e->start++;
	if (s_e->break_point == -1)
	{
		s_e->new_matrix[s_e->i2++] = substring(matrix_exp[s_e->i1++],
			s_e->start, ft_strlen(matrix_exp[s_e->i1]));
	}
	else
	{
		s_e->new_matrix[s_e->i2++] = substring(matrix_exp[s_e->i1],
			s_e->start, s_e->break_point);
		s_e->start = s_e->break_point;
	}
}

static void	env_var_with_space(char **matrix, char **matrix_exp, t_split_env *s_e, t_data *data)
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
			split_env_var_in_space(matrix, matrix_exp, s_e, data);
		s_e->index++;
	}
}

char	**split_env_var_with_space(char **matrix, char **matrix_exp, t_data *data)
{
	t_split_env	*s_e;
	char		**new_matrix;

	s_e = (t_split_env *)ft_calloc(1, sizeof(t_split));
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
/////

int	main(int ac, char **av, char **envp)
{
	char	**matrix;
	char	**matrix_exp;
	char	**new_matrix;
	t_data	data;

	init_data(&data);
	data.envp = get_all_environment(envp);
	matrix = split_2("export:$A$B:$A'---'$B", ':'); // 
	matrix_exp = split_2("export:ab  cdef  gh:ab  cd---ef  gh", ':'); // 
	new_matrix = split_env_var_with_space(matrix, matrix_exp, &data);
	ft_printf("[%i]\n", len_matrix(new_matrix));
	int i = 0;
	while (new_matrix[i])
	{
		ft_printf("[%s]\n", new_matrix[i++]);
	}
	free_matrix(new_matrix);
	free_data(&data);
	return (0);
}
