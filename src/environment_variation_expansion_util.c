/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variation_expansion_util.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_sub(char *env_var, int *end)
{
	int		start;
	char	*sub;

	if (env_var[*end] == '$')
	{
		(*end)++;
		return (NULL);
	}
	start = *end;
	while (env_var[*end] && env_var[*end] != '$')
		(*end)++;
	if (start == *end)
		return (NULL);
	sub = substring(env_var, start, *end);
	(*end)++;
	return (sub);
}

void	get_the_range_of_the_string(char *env_var, int *end)
{
	while ((*end) < (int)ft_strlen(env_var) && env_var[*end]
		&& (ft_isalnum(env_var[*end]) || env_var[*end] == '_'
			|| env_var[*end] == '?'))
		(*end)++;
}

t_index_str	*extracting_the_value_with_single_quotes(char *str,
	t_index_str *index, t_data *data)
{
	char	*env_var;
	char	*value_env_var;

	index->index++;
	while (str[index->index] && (ft_isalnum(str[index->index])
			|| str[index->index] == '_' || str[index->index] == '?'))
		index->index++;
	env_var = substring(str, 1, index->index);
	value_env_var = adjustment_in_the_extraction_string(env_var, data);
	index->str = value_env_var;
	return (free(env_var), index);
}

t_index_str	*exolate_the_content(char *str, t_index_str *index)
{
	int		i;
	char	*env_var;

	i = 0;
	index->index++;
	while (str[index->index] && str[index->index] != '\'')
		index->index++;
	env_var = substring(str, 1, index->index);
	while (str[i] && str[i] == '\'')
		i++;
	index->index += i;
	index->str = env_var;
	return (index);
}
