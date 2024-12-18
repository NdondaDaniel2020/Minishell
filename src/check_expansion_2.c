/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	condition_extract_value_env_quotes(int i, t_new_list *aux)
{
	return (first_str('"', aux->content[0])
		&& (count_chr('"', aux->content[0] + i) % 2 == 0)
		&& (count_chr('\'', aux->content[0] + i) > 0));
}

static void	free_ext(char *value_env, char *aux_env, char *cpy_env, char *mark)
{
	free(value_env);
	free(aux_env);
	free(cpy_env);
	free(mark);
}

void	extract_value_env_quotes(int i, t_new_list *aux, t_data *data)
{
	char	*value_env;
	char	*aux_env;
	char	*mark;
	char	*cpy_env;

	aux_env = ft_strtrim(aux->content[0] + i, "\"'");
	value_env = get_env(aux_env + 1, data);
	if (value_env)
	{
		cpy_env = ft_strdup(value_env);
		mark = ft_strtrim(aux->content[0] + (i + ft_strlen(aux_env)), "\"");
		value_env = ft_strjoin(mark, value_env);
		value_env = ft_strjoin_free(value_env, mark);
		if (is_directory_valid(cpy_env))
		{
			ft_putstr_fd(value_env, 2);
			ft_putstr_fd(": Is a directory\n", 2);
		}
		else
			ft_lstnew_addafter_pos(&data->list,
				data->list, ft_lstnew_new(split_2(value_env, ' ')));
	}
	free_ext(value_env, aux_env, cpy_env, mark);
}
