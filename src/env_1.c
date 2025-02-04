/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *env, t_data *data)
{
	int	i;
	int	ix;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], env, ft_strlen(env))
			&& (data->envp[i][ft_strlen(env)] == '='
			|| data->envp[i][ft_strlen(env)] == '\0'))
		{
			ix = 0;
			while (data->envp[i][ix] && data->envp[i][ix] != '=')
				ix++;
			if (data->envp[i][ix] == '\0')
				return (NULL);
			return (data->envp[i] + ix + 1);
		}
		i++;
	}
	return (NULL);
}

static void	put_error_env(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
}

static bool	expanded_env_error(t_new_list *aux, t_data *data)
{
	char	*env;

	env = get_env(aux->content[1] + 1, data);
	if (env)
	{
		put_error_env("env: ‘", env, "’: Permission denied\n");
		return (true);
	}
	return (false);
}

static int	check_erro_env(t_new_list *aux, t_data *data)
{
	int		len;

	if (len_matrix(aux->content) > 1)
	{
		len = ft_strlen(aux->content[get_last_position(aux)]);
		if (len > 0 && aux->content[get_last_position(aux)]
			&& !ft_strchr(aux->content[get_last_position(aux)], '$')
			&& ft_strncmp(aux->content[get_last_position(aux)], "env", 4))
		{
			put_error_env("env: ‘", aux->content[get_last_position(aux)],
				"’: No such file or directory\n");
			return (127);
		}
		else if (len > 0 && aux->content[get_last_position(aux)]
			&& ft_strchr(aux->content[get_last_position(aux)], '$')
			&& ft_strncmp(aux->content[get_last_position(aux)], "env", 4))
		{
			if (expanded_env_error(aux, data))
				return (126);
		}
	}
	return (0);
}

int	env(t_new_list *aux, t_data *data)
{
	int	i;
	int	err;

	i = 0;
	err = check_erro_env(aux, data);
	if (err)
		return (change_environment_variables_question_mark(err, data));
	while (data->envp[i])
	{
		if (ft_strchr(data->envp[i], '=') && !ft_strchr(data->envp[i], '?'))
			ft_printf("%s\n", data->envp[i]);
		i++;
	}
	return (change_environment_variables_question_mark(0, data));
}
