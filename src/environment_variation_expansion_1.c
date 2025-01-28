/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variation_expansion_1.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_extract(char *str, int index)
{
	int		i;
	char	*str_aux;

	str_aux = ft_substr(str, 0, index + 1);
	i = count_chr('$', str_aux);
	if (i == 1 && str[index] == ' ')
		return (free(str_aux), false);
	return (free(str_aux), true);
}

char	*adjustment_in_the_extraction_string(char *str, t_data *data)
{
	char	*aux;
	char	*void_str;

	aux = get_env(str, data);
	if (aux == NULL)
	{
		void_str = ft_calloc(1, sizeof(char));
		return (void_str);
	}
	return (ft_strdup(aux));
}

void	environment_variation_expansion(char ***matrix, t_data *data)
{
	int		i;
	int		old_size;
	int		new_size;
	char	*value_env;

	if ((*matrix) == NULL)
		return ;
	i = 0;
	while ((*matrix)[i])
	{
		if (i > 0 && (ft_strchr((*matrix)[i], '$')
			|| ft_strchr((*matrix)[i], '\'') || ft_strchr((*matrix)[i], '\"')))
		{
			value_env = get_environment_variation_expansion((*matrix)[i], data);
			old_size = ft_strlen((*matrix)[i]);
			new_size = ft_strlen(value_env);
			(*matrix)[i] = ft_realloc((*matrix)[i], old_size, new_size + 1);
			ft_strlcpy((*matrix)[i], value_env, new_size + 1);
			free(value_env);
		}
		i++;
	}
}
