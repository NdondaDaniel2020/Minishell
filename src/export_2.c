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

static void	init_environment_variable(int *i, bool *unique, bool *is_equal)
{
	*i = 0;
	*unique = true;
	*is_equal = false;
}

static void	reallocation_envp(int i, char *env_var, t_data *data)
{
	data->envp = ft_realloc((void *)data->envp,
			sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	data->envp[i] = env_var;
	data->envp[i + 1] = NULL;
}

static void	reallocation_envp_str(int point_equal, char *env_var, t_data *data)
{
	free(data->envp[point_equal]);
	data->envp[point_equal] = env_var;
}

void	add_environment_variable(char *env_var, t_data *data)
{
	int		i;
	int		point_equal;
	bool	unique;
	bool	is_equal;

	init_environment_variable(&i, &unique, &is_equal);
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
		reallocation_envp(i, env_var, data);
	else if (is_equal)
		reallocation_envp_str(point_equal, env_var, data);
	change_environment_variables_question_mark(0, data);
}
