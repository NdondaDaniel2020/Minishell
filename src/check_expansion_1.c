/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	condition_put_env_quotes(int i, t_new_list *aux)
{
	return (first_str('\'', aux->content[0])
		&& (count_chr('\'', aux->content[0] + i) % 2 != 0)
		&& (count_chr('"', aux->content[0] + i) > 0));
}

static bool	condition_put_env(int i, t_new_list *aux)
{
	return ((count_chr('"', aux->content[0]) == 0
			&& (count_chr('\'', aux->content[0] + i) % 2 != 0))
		|| (first_str('"', aux->content[0])
			&& (count_chr('"', aux->content[0] + i) % 2 == 0)
			&& (count_chr('\'', aux->content[0] + i) > 0)));
}

static bool	condition_extract_value_env(int i, t_new_list *aux)
{
	return ((count_chr('"', aux->content[0] + i) == 0
			&& count_chr('\'', aux->content[0] + i) == 0)
		|| (count_chr('\'', aux->content[0] + i) == 0
			&& (count_chr('"', aux->content[0] + i) > 0))
		|| (count_chr('"', aux->content[0] + i) == 0
			&& (count_chr('\'', aux->content[0] + i) % 2 == 0))
		|| (first_str('\'', aux->content[0])
			&& (count_chr('\'', aux->content[0] + i) % 2 == 0)
			&& (count_chr('"', aux->content[0] + i) > 0)));
}

static void	extract_value_env(int i, t_new_list *aux, t_data *data)
{
	char	*value_env;
	char	*aux_env;

	aux_env = ft_strtrim(aux->content[0] + i, "\"'");
	value_env = get_env(aux_env + 1, data);
	if (value_env)
	{
		if (is_directory_valid(value_env))
		{
			ft_putstr_fd(value_env, 2);
			ft_putstr_fd(": Is a directory\n", 2);
		}
		else
		{
			value_env = ft_strtrim(value_env, "\"'");
			ft_lstnew_addback(&data->list,
				ft_lstnew_new(split_2(value_env, ' ')));
			free(value_env);
		}
	}
	free(aux_env);
}

void	check_environment_variable_expansion(t_new_list *aux, t_data *data)
{
	int		i;
	char	*value_env;

	i = 0;
	while (aux->content[0][i] && aux->content[0][i] != '$')
		i++;
	if (condition_extract_value_env(i, aux))
		extract_value_env(i, aux, data);
	else if (condition_put_env(i, aux))
	{
		ft_putstr_fd(aux->content[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (condition_extract_value_env_quotes(i, aux))
		extract_value_env_quotes(i, aux, data);
	else if (condition_put_env_quotes(i, aux))
	{
		value_env = ft_strtrim(aux->content[0], "'");
		ft_putstr_fd(value_env, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(value_env);
	}
}
