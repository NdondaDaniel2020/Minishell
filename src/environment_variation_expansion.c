/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variation_expansion.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_value_env(char *str, t_data *data)
{
	int		i;
	int		len;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	if (str[i] == '$' && (i + 1) < len)
		return (extracting_the_value_with_single_quotes(str, data));
	else if (str[i] == '\'')
		return (exolate_the_content(str));
	else if (str[i] == '\"')
		return (exolate_the_content_with_double_quotes(str, data));
	return (NULL);
}

static int	adjust_position(char *str)
{
	int		i;
	int		len;
	char	chr;

	i = 0;
	if (!str)
		return (0);
	len = ft_strlen(str);
	if (str[i] == '$' && (i + 1) < len)
	{
		i++;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
			i++;
	}
	else if (str[i] == '\'' || str[i] == '\"')
	{
		chr = str[i];
		i++;
		while (str[i] && str[i] != chr)
			i++;
	}
	return (i);
}

static void	join_values(char **join, char *value_env, int *pos, char *str)
{
	if ((*join) == NULL)
	{
		if (ft_strlen(value_env) == 0)
			(*pos) += 2;
		else
			(*pos) += adjust_position(str + (*pos));
		(*join) = value_env;
	}
	else
	{
		if (ft_strlen(value_env) == 0)
			(*pos) += 2;
		else
			(*pos) += adjust_position(str + (*pos));
		(*join) = ft_strjoin_free((*join), value_env);
		free(value_env);
	}
}

char	*get_environment_variation_expansion(char *str, t_data *data)
{
	int		len;
	int		pos;
	char	*join;
	char	*value_env;

	pos = 0;
	join = NULL;
	len = ft_strlen(str);
	while (pos < len - 1)
	{
		value_env = extract_value_env(str + pos, data);
		if (value_env)
			join_values(&join, value_env, &pos, str);
		else
		{
			if (join == NULL)
				join = ft_charjoin(NULL, str[pos]);
			else
				join = ft_charjoin_free(join, str[pos]);
			pos++;
		}
	}
	return (join);
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
		if (ft_strchr((*matrix)[i], '$') || ft_strchr((*matrix)[i], '\'')
			|| ft_strchr((*matrix)[i], '"'))
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
