/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variation_expansion_2.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*invert_str(char *str)
{
	int		i;
	int		len;
	char	*new_string;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	new_string = ft_calloc(len + 1, sizeof(char));
	while (str[i])
		new_string[len-- - 1] = str[i++];
	return (new_string);
}

char	*extract_value_env_quotes(char *str, char *sub, t_data *data)
{
	int		end;
	int		start;
	char	*aux;
	char	*sub_str;
	char	*inv_sub;

	start = 0;
	while (str[start] != '$')
		start++;
	end = start + 1;
	while (ft_isalpha(str[end]))
		end++;
	aux = ft_strtrim(sub, "\"");
	inv_sub = invert_str(aux);
	free(aux);
	sub_str = substring(str, start, end);
	aux = ft_strdup(get_env(sub_str + 1, data));
	free(sub_str);
	sub_str = ft_strjoin(inv_sub, aux);
	free(aux);
	aux = ft_strjoin_free(sub_str, inv_sub);
	free(inv_sub);
	return (aux);
}

static void	join_value_env(t_index_str *value_env, char **join, int *pos)
{
	if ((*join) == NULL)
	{
		(*pos) += value_env->index;
		(*join) = value_env->str;
	}
	else
	{
		(*pos) += value_env->index;
		if (ft_strlen(value_env->str) == 0)
			(*join) = ft_charjoin_free((*join), 1);
		else
			(*join) = ft_strjoin_free((*join), value_env->str);
		free(value_env->str);
	}
}

char	*get_environment_variation_expansion(char *str, t_data *data)
{
	int			len;
	int			pos;
	char		*join;
	t_index_str	*value_env;

	pos = 0;
	join = NULL;
	len = ft_strlen(str);
	while (pos < len - 1)
	{
		value_env = extract_value_env(str + pos, data);
		if (value_env->str)
			join_value_env(value_env, &join, &pos);
		else
		{
			if (join == NULL)
				join = ft_charjoin(NULL, str[pos]);
			else
				join = ft_charjoin_free(join, str[pos]);
			pos++;
		}
		free(value_env);
	}
	return (join);
}

t_index_str	*extract_value_env(char *str, t_data *data)
{
	int			len;
	t_index_str	*index;

	if (!str)
		return (NULL);
	index = ft_calloc(1, sizeof(t_index_str));
	index->index = 0;
	index->str = NULL;
	len = ft_strlen(str);
	if (str[index->index] == '$' && (index->index + 1) < len)
		return (extracting_the_value_with_single_quotes(str, index, data));
	else if (str[index->index] == '\'')
		return (exolate_the_content(str, index));
	else if (str[index->index] == '\"')
		return (exolate_the_content_with_double_quotes(str, index, data));
	return (index);
}
