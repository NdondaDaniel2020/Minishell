/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variation_expansion_extract_main.c      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:26 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/09 12:04:37 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*treat_string(char *sub)
{
	int i;

	i = 0;
	while (sub[i] == '\'' || sub[i] == '"')
		i++;
	if (count_chr('\'', sub) == 0 && count_chr('"', sub) == 0)
		return (ft_strdup(sub));
	else if ((count_chr('\'', sub) > 0 && count_chr('"', sub) == 0)
		|| (count_chr('\'', sub) == 0 && count_chr('"', sub) > 0)
		|| (first_str('"', sub) && (count_chr('"', sub + i) % 2 == 0)
			&& (count_chr('\'', sub) > 0))
		|| (first_str('\'', sub) && (count_chr('\'', sub + i) % 2 == 0)
			&& (count_chr('"', sub) > 0)))
		return (put_env_environment(sub));
	else if (first_str('"', sub) && (count_chr('"', sub + 1) % 2 != 0)
		&& (count_chr('\'', sub) > 0))
		return (str_quotes(sub, "\""));
	else if (first_str('\'', sub) && (count_chr('\'', sub + 1) % 2 != 0)
		&& (count_chr('"', sub) > 0))
		return (str_quotes(sub, "'"));
	return (ft_strdup(sub));
}

static bool	all_is_quotes(char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (*str != '"' && *str != '\'')
			return (false);
		str++;
	}
	return (true);
}

char	*extract_main_value_env(char *str, t_data *data)
{
	char	*sub;
	char	*result;

	sub = ft_substr(str, 0, ft_strchr(str, '$') - str);
	if (all_is_quotes(sub))
	{
		if (condition_put_env_environment(str, sub))
			result = put_env_environment(str);
		else if (condition_extract_value_env(str, sub))
			result = extract_value_env(str, data);
		else if (condition_extract_value_env_quotes(str, sub))
			result = extract_value_env_quotes(str, sub, data);
		else if (condition_put_env_quotes(str, sub))
			result = put_env_quotes(str, sub);
	}
	else
		result = treat_string(sub);
	free(sub);
	return (result);
}
