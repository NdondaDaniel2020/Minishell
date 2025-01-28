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

static t_index_str	*exolate_double_and_single_quotes(char *env_var,
	t_index_str *index, t_data *data)
{
	char	*sub;
	char	*value_env_var;

	sub = ft_substr(env_var, 0, ft_strchr(env_var, '$') - env_var);
	value_env_var = extract_value_env_quotes(env_var, sub, data);
	index->index = ft_strchr(env_var, '$') - env_var;
	index->str = value_env_var;
	free(env_var);
	free(sub);
	return (index);
}

static t_index_str	*exude_content_without_double_quotes(char *str,
	char *env_var, t_index_str *index, t_data *data)
{
	int		i;
	char	*sub;

	i = 0;
	if (env_var[0] == '$')
	{
		sub = adjustment_in_the_extraction_string(env_var + 1, data);
		index->index = ft_strlen(env_var);
		index->str = sub;
		while (str[i] && str[i] == '"')
			i++;
		index->index += i;
		free(env_var);
		return (index);
	}
	index->index = 0;
	while (env_var[index->index] && env_var[index->index] != '$')
		index->index++;
	sub = substring(env_var, 0, index->index);
	while (str[i] && str[i] == '"')
		i++;
	index->index += i;
	index->str = sub;
	free(env_var);
	return (index);
}

t_index_str	*exolate_the_content_with_double_quotes(char *str,
	t_index_str *index, t_data *data)
{
	int		i;
	char	*env_var;

	i = 0;
	index->index++;
	while (str[index->index] && str[index->index] != '\"'
		&& valid_extract(str, index->index))
		index->index++;
	env_var = substring(str, 1, index->index);
	if (ft_strchr(env_var, '\'') && ft_strchr(env_var, '$'))
		return (exolate_double_and_single_quotes(env_var, index, data));
	else if (ft_strchr(env_var, '$'))
		return (exude_content_without_double_quotes(str, env_var, index, data));
	index->str = env_var;
	while (str[i] && str[i] == '"')
		i++;
	index->index += i;
	return (index);
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
