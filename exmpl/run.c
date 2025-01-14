/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:26 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/09 12:04:37 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

char	*substring(const char *str, int start, int end)
{
	int 	len;
	char	*sub;

	len = strlen(str);
	if (start > end)
		return (NULL);
	if (start < 0)
		start = 0;
	if (end > len)
		end = len;
	sub = (char *)malloc((end - start + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, str + start, end - start + 1);
	sub[end - start] = '\0';
	return (sub);
}

///////////
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

bool	condition_put_env_quotes(char *str, char *sub) // """$USER"""
{
	return (first_str('\'', str) && (count_chr('\'', sub) % 2 != 0)
		&& (count_chr('"', sub) > 0));
}

bool	condition_extract_value_env_quotes(char *str, char *sub) // '''name'''
{
	return (first_str('"', str) && (count_chr('"', sub) % 2 != 0)
		&& (count_chr('\'', sub) > 0));
}

bool	condition_put_env(char *str, char *sub) // $USER
{
	return ((count_chr('"', str) == 0 && (count_chr('\'', sub) % 2 != 0))
		 || (first_str('"', str) && (count_chr('"', sub) % 2 == 0)
		 		&& (count_chr('\'', sub) > 0)));
}

bool	condition_extract_value_env(char *str, char *sub) // name
{
	return ((count_chr('"', sub) == 0 && count_chr('\'', sub) == 0)
		 || (count_chr('\'', sub) == 0 && (count_chr('"', sub) > 0))
		 || (count_chr('"', sub) == 0 && (count_chr('\'', sub) % 2 == 0))
		 || (first_str('\'', str) && (count_chr('\'', sub) % 2 == 0)
		 	&& (count_chr('"', sub) > 0)));
}
///////////

///////////
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

char	*extract_value_env(int i_pos, char *str, t_data *data)
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
	if (i_pos == 0)
		value_env = ft_strdup(get_env(aux + pos, data));
	else
		value_env = get_env(aux + pos, data);
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

//////////

char	*str_quotes(char *str, char *chr)
{
	char	*sub_str;

	sub_str = ft_strtrim(str, chr);
	return (sub_str);
}

char	*treat_string(char *sub) /// error
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
		return (put_env(sub));
	else if (first_str('"', sub) && (count_chr('"', sub + 1) % 2 != 0)
		&& (count_chr('\'', sub) > 0))
		return (str_quotes(sub, "\""));
	else if (first_str('\'', sub) && (count_chr('\'', sub + 1) % 2 != 0)
		&& (count_chr('"', sub) > 0))
		return (str_quotes(sub, "'"));
}

bool	all_is_quotes(char *str)
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

char	*extract_main_value_env(int i, int pos, char *str, t_data *data)
{
	char	*sub;
	char	*result;

	sub = ft_substr(str, 0, ft_strchr(str, '$') - str);
	if (all_is_quotes(sub))
	{
		if (condition_put_env(str, sub))
			result = put_env(str);
		else if (condition_extract_value_env(str, sub))
			result = extract_value_env(pos, str, data);
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

///////////
static int	adjust_position_variation(int pos, char *sub, char *str, t_data *data)
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

char	*get_environment_variation_expansion(int i, char ***matrix, t_data *data)
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
		value_env = extract_main_value_env(i, pos, (*matrix)[i] + pos, data);
		sub = ft_substr(((*matrix)[i] + pos), 0, ft_strchr(((*matrix)[i] + pos), '$') - ((*matrix)[i] + pos));
		if (value_env && sub && ft_strnstr(sub, value_env, ft_strlen(sub)))
			pos += ft_strlen(sub);
		else
			pos = adjust_position_variation(pos, sub, (*matrix)[i], data);

//////////////////////////////////////////////////////////////////////////////
		if (join == NULL)
			join = ft_strjoin_free(value_env, join);
		else
			join = ft_strjoin_free(join, value_env);
//////////////////////////////////////////////////////////////////////////////

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

int	main(void)
{
	int		i;
	t_data	data;
	char	**matrix;

	i = 0;
	init_data(&data);
	data.envp = get_all_environment();
	matrix = split_2("echo: $USER ", ':');
	environment_variation_expansion(&matrix, &data);
	while (matrix[i])
	{
		printf("[%s]\n", matrix[i]);
		i++;
	}
	free_matrix(matrix);
	free_data(&data);
	return (0);
}
