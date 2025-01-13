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

char	*extract_value_env(int i, char *str, t_data *data)
{
	char	*sub;

	sub = ft_substr(str, 0, ft_strchr(str, '$') - str);
	if (condition_put_env(str, sub))
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
		free(value_env);
		aux = substring(str, 0, end);
		free(sub);
		return (aux);
	}
	else if (condition_extract_value_env(str, sub)) // V/
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
		free(value_env);
		aux = substring(str, 0, end);
		pos = 0;
		while (aux[pos] && aux[pos] == '$')
			pos++;
		value_env = ft_strdup(get_env(aux + pos, data));
		free(sub);
		return (value_env);
	}
	else if (condition_extract_value_env_quotes(str, sub))
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
		free(sub);
		return (aux);
	}
	else if (condition_put_env_quotes(str, sub))
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
		free(sub);
		return (aux);
	}
	return (NULL);
}

///////////





// void	check_environment_variable_expansion(char **str, t_data *data)

static int	adjust_position_variation(int pos, char *sub, char *str, t_data *data)
{
	int len;

	len = ft_strlen(str);

	if (pos == 0)
		pos = ft_strlen(sub);
	if (str[pos] == '$')
		pos++;
	while ((pos < len) && str[pos] != '\''
		&& str[pos] != '"' && str[pos] != '$')
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
		value_env = extract_value_env(i, (*matrix)[i] + pos, data);
		sub = ft_substr(((*matrix)[i] + pos), 0,
			ft_strchr(((*matrix)[i] + pos), '$') - ((*matrix)[i] + pos));
		pos += adjust_position_variation(pos, sub, (*matrix)[i], data);
		if (join == NULL)
			join = ft_strjoin_free(value_env, join);
		else
			join = ft_strjoin_free(join, value_env);
		free(sub);
	}
	free(value_env);
	return (join);
}

void	environment_variation_expansion(int i, char ***matrix, t_data *data)
{
	int		old_size;
	int		new_size;
	char	*value_env;

	value_env = get_environment_variation_expansion(i, matrix, data);
	old_size = ft_strlen((*matrix)[i]);
	new_size = ft_strlen(value_env);
	(*matrix)[i] = ft_realloc((*matrix)[i], old_size, new_size + 1);
	ft_strlcpy((*matrix)[i], value_env, new_size + 1);
	free(value_env);
}

int	main(void)
{
	int		i;
	t_data	data;
	char	**matrix;

	i = 0;
	init_data(&data);
	data.envp = get_all_environment();
	matrix = split_2("echo:'\"$USER\"''\"$HOME\"'", ':');
	while (matrix[i])
	{
		if (ft_strchr(matrix[i], '$'))
			environment_variation_expansion(i, &matrix, &data);
		ft_printf("[[%s]]\n", matrix[i]);
		i++;
	}
	free_matrix(matrix);
	free_data(&data);
	return (0);
}
