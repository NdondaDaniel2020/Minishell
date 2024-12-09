/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*reorganization(char *env, int len)
{
	int		i;
	char	*new_env;

	i = 0;
	new_env = (char *) malloc(len + 3);
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i] != '=')
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = env[i];
	i++;
	new_env[i] = '"';
	i++;
	ft_strlcpy(new_env + i, env + i - 1, len);
	new_env[len + 1] = '"';
	new_env[len + 2] = '\0';
	return (new_env);
}

static char	*analize_env(char *env)
{
	int	i;
	int	len;
	int	count_equals;

	i = 0;
	len = ft_strlen(env);
	count_equals = 0;
	while (i < len)
	{
		if (env[i] == '=')
			count_equals++;
		i++;
	}
	if (count_equals > 1 || env[len - 1] == '=')
	{
		return (reorganization(env, len));
	}
	return (ft_strdup(env));
}

void	add_environment_variable(char *env_var, t_data *data)
{
	int		i;
	int		point_equal;
	bool	unique;
	bool	is_equal;

	i = 0;
	unique = true;
	is_equal = false;
	while (data->envp[i])
	{
		if (!ft_strncmp(env_var, data->envp[i], ft_strlen(env_var)))
			unique = false;
		if (!ft_strnchrcmp(env_var, data->envp[i],
				ft_strlen(data->envp[i]), '='))
		{
			is_equal = true;
			point_equal = i;
		}
		i++;
	}
	env_var = analize_env(env_var);
	if (unique && !is_equal)
	{
		data->envp = ft_realloc((void *)data->envp,
				sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
		data->envp[i] = env_var;
		data->envp[i + 1] = NULL;
	}
	else if (is_equal)
	{
		free(data->envp[point_equal]);
		data->envp[point_equal] = env_var;
	}
	change_environment_variables_question_mark(0, data);
}

void	change_environment_variables_question_mark(int value, t_data *data)
{
	int		i;
	int		len;
	char	*new_env;
	char	*value_str;

	i = 0;
	while (data->envp[i])
		i++;
	if (ft_atoi(data->envp[i - 1] + 2) != value)
	{
		len = ft_nblen(value, 10);
		new_env = ft_calloc(3 + len, sizeof(char));
		if (!new_env)
			return ;
		ft_strlcpy(new_env, "?=", 3);
		value_str = ft_itoa(value);
		new_env = ft_strjoin_free(new_env, value_str);
		free(data->envp[i - 1]);
		data->envp[i - 1] = new_env;
		free(value_str);
	}
}
