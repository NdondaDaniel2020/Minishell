/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*reorganization(char *env, int len)
{
	int		i;
	char	*new_env;

	i = 0;
	new_env = (char *) malloc(len + 3);
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i] != '=')
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = env[i];
	i++;
	new_env[i] = '"';
	i++;
	ft_strlcpy(new_env + i, env + i - 1, len);
	new_env[len + 1] = '"';
	new_env[len + 2] = '\0';
	return (new_env);
}

char	*analize_env(char *env)
{
	int	i;
	int	len;
	int	count_equals;

	i = 0;
	len = ft_strlen(env);
	count_equals = 0;
	while (i < len)
	{
		if (env[i] == '=')
			count_equals++;
		i++;
	}
	if (count_equals > 1 || env[len - 1] == '=')
	{
		return (reorganization(env, len));
	}
	return (ft_strdup(env));
}

int	is_valid_char(char c)
{
	if (c == '_' || c == '=' || c == '\'' || c == '\"' || c == '$' || c == '\\')
		return (1);
	if (c == ' ' || c == '.' || c == '/' || c == ':' || c == '-' || c == '+')
		return (1);
	return (0);
}
