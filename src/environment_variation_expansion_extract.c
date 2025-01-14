/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variation_expansion_extract.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:26 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/09 12:04:37 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

char	*put_env(char *str)
{
	int 	pos;
	int		end;
	char	*aux;
	char	*value_env;

	value_env = ft_strtrim(str, "'\"");
	pos = 0;
	while (value_env[pos] && value_env[pos] == '$')
		pos++;
	end  = pos + 1;
	while (value_env[end] && value_env[end] != '$'
		&& value_env[end] != '\'' && value_env[end] != '"')
		end++;
	aux = substring(value_env, 0, end);
	free(value_env);
	return (aux);
}

char	*extract_value_env(char *str, t_data *data)
{
	int 	pos;
	int		end;
	char	*aux;
	char	*value_env;

	value_env = ft_strtrim(str, "'\"");
	pos = 0;
	while (value_env[pos] && value_env[pos] == '$')
		pos++;
	end  = pos + 1;
	while (ft_isalpha(value_env[end]) || value_env[end] == '?'
			|| value_env[end] == '_')
		end++;
	aux = substring(value_env, 0, end);
	free(value_env);
	pos = 0;
	while (aux[pos] && aux[pos] == '$')
		pos++;
	value_env = ft_strdup(get_env(aux + pos, data));
	free(aux);
	return (value_env);
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

char	*put_env_quotes(char *str, char *sub)
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
	aux = ft_strtrim(sub, "'");
	inv_sub = invert_str(aux);
	free(aux);
	sub_str = substring(str, start, end);
	aux = ft_strdup(sub_str);
	free(sub_str);
	sub_str = ft_strjoin(inv_sub, aux);
	free(aux);
	aux = ft_strjoin_free(sub_str, inv_sub);
	free(inv_sub);
	return (aux);
}

char	*str_quotes(char *str, char *chr)
{
	char	*sub_str;

	sub_str = ft_strtrim(str, chr);
	return (sub_str);
}
