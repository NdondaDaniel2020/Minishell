/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variation_expansion.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:26 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/09 12:04:37 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	adjust_position_variation(int pos, char *sub, char *str)
{
	int len;

	len = ft_strlen(str);
	if (pos == 0)
		pos = ft_strlen(sub);
	if (str[pos] == '$')
		pos++;
	while ((pos < len) && (ft_isalpha(str[pos])
		|| str[pos] == '?'|| str[pos] == '_'))
		pos++;
	pos += ft_strlen(sub);
	return (pos);
}

static void	join_value_env(char **join, char *value_env)
{
	if ((*join) == NULL)
		(*join) = ft_strdup(value_env);
	else
		(*join) = ft_strjoin_free((*join), value_env);
}

static char	*get_environment_variation_expansion(int i, char ***matrix, t_data *data)
{
	int		len;
	int		pos;
	char	*sub;
	char	*join;
	char	*value_env;

	pos = 0;
	join = NULL;
	len = ft_strlen((*matrix)[i]);
	while (pos < len)
	{
		value_env = extract_main_value_env((*matrix)[i] + pos, data);
		sub = ft_substr(((*matrix)[i] + pos), 0,
			ft_strchr(((*matrix)[i] + pos), '$') - ((*matrix)[i] + pos));
		if (value_env && sub && ft_strnstr(sub, value_env, ft_strlen(sub)))
			pos += ft_strlen(sub);
		else
			pos = adjust_position_variation(pos, sub, (*matrix)[i]);
		join_value_env(&join, value_env);
		free(value_env);
		free(sub);
	}
	return (join);
}

void	environment_variation_expansion(char ***matrix, t_data *data)
{
	int		i;
	int		old_size;
	int		new_size;
	char	*value_env;

	i = 0;
	while ((*matrix)[i])
	{
		if (ft_strchr((*matrix)[i], '$'))
		{
			value_env = get_environment_variation_expansion(i, matrix, data);
			old_size = ft_strlen((*matrix)[i]);
			new_size = ft_strlen(value_env);
			(*matrix)[i] = ft_realloc((*matrix)[i], old_size, new_size + 1);
			ft_strlcpy((*matrix)[i], value_env, new_size + 1);
			free(value_env);
		}
		i++;
	}
}
