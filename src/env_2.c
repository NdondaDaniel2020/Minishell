/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_shlvl_value(const char *shlvl_str)
{
	size_t	prefix_len;

	prefix_len = 6;
	if (strncmp(shlvl_str, "SHLVL=", prefix_len) != 0)
		return (-1);
	return (atoi(shlvl_str + prefix_len));
}

static void	int_to_str(int num, char *buffer)
{
	int	len;
	int	temp;

	len = 0;
	temp = num;
	while (temp > 0)
	{
		len++;
		temp /= 10;
	}
	if (num == 0)
		len = 1;
	buffer[len] = '\0';
	while (len > 0)
	{
		buffer[--len] = (num % 10) + '0';
		num /= 10;
	}
}

static char	*increment_shlv(char *shlvl_str)
{
	int		shlvl;
	char	*new_shlvl_str;
	char	shlvl_str_value[12];
	size_t	prefix_len;
	size_t	new_str_len;

	prefix_len = 6;
	shlvl = get_shlvl_value(shlvl_str);
	if (shlvl == -1)
		return (NULL);
	shlvl++;
	int_to_str(shlvl, shlvl_str_value);
	new_str_len = prefix_len + strlen(shlvl_str_value) + 1;
	new_shlvl_str = (char *)malloc(new_str_len);
	if (new_shlvl_str == NULL)
		return (NULL);
	ft_strlcpy(new_shlvl_str, "SHLVL=", 7);
	ft_strlcat(new_shlvl_str, shlvl_str_value,
		ft_strlen(new_shlvl_str) + ft_strlen(new_shlvl_str) + 1);
	free(shlvl_str);
	return (new_shlvl_str);
}

char	**get_all_environment(char **envp)
{
	int		i;
	char	*env;
	char	**new_env;

	i = len_matrix(envp);
	new_env = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		env = ft_strdup(envp[i]);
		if (!ft_strncmp(env, "SHLVL", ft_strlen(env) - 2))
			env = increment_shlv(env);
		new_env[i] = env;
		i++;
	}
	new_env[i] = ft_strdup("?=0");
	return (new_env);
}
