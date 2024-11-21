/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*create_aux_env(t_data *data)
{
	int		i1;
	char	**aux_env;

	i1 = 0;
	while (data->envp[i1])
		i1++;
	aux_env = ft_calloc(i1, sizeof(char *));
	if (!aux_env)
	{
		return (NULL);
	}
	return (aux_env);
}

static void	free_env(char **aux_env, bool *is_removed, t_data *data)
{
	if (*is_removed)
	{
		free(data->envp);
		data->envp = aux_env;
	}
	else
		free(aux_env);
}

void	remove_env(int i1, char *env, t_data *data)
{
	int		i2;
	bool	is_removed;
	char	**aux_env;

	i2 = 0;
	is_removed = false;
	aux_env = create_aux_env(data);
	if (!aux_env)
		return ;
	while (data->envp[i1])
	{
		if (!ft_strncmp(env, data->envp[i1], ft_strlen(env)))
		{
			is_removed = true;
			free(data->envp[i1]);
		}
		else
		{
			aux_env[i2] = data->envp[i1];
			i2++;
		}
		i1++;
	}
	free_env(aux_env, &is_removed, data);
}

void	unset(t_data *data)
{
	int	i;
	int	i1;

	i = 1;
	i1 = 0;
	while (data->btree->content[i])
	{
		remove_env(i1, data->btree->content[i], data);
		i++;
	}
}
