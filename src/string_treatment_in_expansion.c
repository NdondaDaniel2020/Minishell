/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_treatment_in_expansion.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*invert_str(char *str)
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
	int 	end;
	int 	start;
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

char	*extracting_the_value_with_single_quotes(char *str, t_data *data)
{
	int		i;
	char	*env_var;
	char	*value_env_var;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
		i++;
	env_var = substring(str, 1, i);
	value_env_var = ft_strdup(get_env(env_var, data));
	return (free(env_var), value_env_var);	
}

char	*exolate_the_content(char *str)
{
	int		i;
	char	*env_var;

	i = 1;
	while (str[i] && str[i] != '\'')
		i++;
	env_var = substring(str, 1, i);
	return (env_var);
}

char	*exolate_the_content_with_double_quotes(char *str, t_data *data)
{
	int		i;
	char	*sub;
	char	*env_var;
	char	*value_env_var;

	i = 1;
	while (str[i] && str[i] != '\"')
		i++;
	env_var = substring(str, 1, i);
	if (ft_strchr(env_var, '\'') && ft_strchr(env_var, '$'))
	{
		sub = ft_substr(env_var, 0, ft_strchr(env_var, '$') - env_var);
		value_env_var = extract_value_env_quotes(env_var, sub, data);
		free(env_var);
		free(sub);
		return (value_env_var);
	}
	return (env_var);
}
