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
			while (data->envp[i][ix] != '=')
				ix++;
			return (data->envp[i] + ix + 1);
		}
		i++;
	}
	return (NULL);
}

int	len_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
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

void	env(t_new_list *aux, t_data *data)
{
	int		i;
	int		len;

	i = 0;
	if (len_matrix(aux->content) > 1)
	{
		len = ft_strlen(aux->content[1]);
		if (len > 0 && aux->content[1] && !ft_strchr(aux->content[1], '$'))
		{
			put_error_env("env: ‘", aux->content[1],
				"’: No such file or directory\n");
			return ;
		}
		else if (len > 0 && aux->content[1] && ft_strchr(aux->content[1], '$'))
		{
			if (expanded_env_error(aux, data))
				return ;
		}
	}
	while (data->envp[i])
	{
		if (ft_strchr(data->envp[i], '=') && !ft_strchr(data->envp[i], '?'))
			ft_printf("%s\n", data->envp[i]);
		i++;
	}
}
