/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
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
		data->envp = ft_realloc((void *)data->envp, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
		data->envp[i] = ft_strdup(env_var);
		data->envp[i + 1] = NULL;
		free(env_var);
	}
	else if (is_equal)
	{
		free(data->envp[point_equal]);
		data->envp[point_equal] = ft_strdup(env_var);
	}

	if (data->automatic_input)
	{
		data->automatic_input = false;
		free(env_var);
	}
}
