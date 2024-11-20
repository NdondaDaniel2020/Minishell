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

void	remove_env(char *env, t_data *data)
{
    int		i1;
    int		i2;
    bool	is_removed;
    char	**aux_env;

    i1 = 0;
    i2 = 0;
    is_removed = false;
    while (data->envp[i1])
        i1++;
    aux_env = ft_calloc(i1, sizeof(char *));
    if (!aux_env)
        return ;
    i1 = 0;
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
    if (is_removed)
    {
        free(data->envp);
        data->envp = aux_env;
    }
    else
    {
        free(aux_env);
    }
}

void	unset(t_data *data)
{
	int	i;

	i = 1;
	while (data->btree->content[i])
	{
		remove_env(data->btree->content[i], data);
		i++;
	}
}

