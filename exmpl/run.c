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

/* usa o tipo index para fazer o ++ e add no index*/

#include "run.h"

char	*ft_charjoin_free(char *s1, char c)
{
	char	*join;
	int		l1;
	int		i;

	if (!s1 && !c)
		return (NULL);
	i = 0;
	l1 = ft_strlen(s1);
	join = malloc((l1 + 2) * sizeof(char));
	if (!join)
		return (NULL);
	while (i < (l1 + 1))
	{
		if (i < l1)
			join[i] = s1[i];
		else
			join[i] = c;
		i++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
}

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

t_index_str	*extract_value_env(char *str, t_data *data)
{
	int		i;
	int		len;
	char	*env_var;
	char	*value_env_var;
	t_index_str	*index;

	if (!str)
		return (NULL);

	index = ft_calloc(1, sizeof(t_index_str));
	index->index = 0;
	index->str = NULL;

	i = 0;
	len = ft_strlen(str);
	if (str[index->index] == '$' && (index->index + 1) < len)
	{
		index->index++;
		while (str[index->index] && (ft_isalnum(str[index->index])
			|| str[index->index] == '_' || str[index->index] == '?'))
			index->index++;
		env_var = substring(str, 1, index->index);
		value_env_var = ft_strdup(get_env(env_var, data));
		index->str = value_env_var;
		return (free(env_var), index);
	}
	else if (str[index->index] == '\'')
	{
		index->index++;
		while (str[index->index] && str[index->index] != '\'')
			index->index++;
		env_var = substring(str, 1, index->index);
		index->str = env_var;
		return (index);
	}
	else if (str[i] == '\"')
	{
		char	*sub;
	
		index->index++;
		while (str[index->index] && str[index->index] != '\"')
			index->index++;
		env_var = substring(str, 1, index->index);

		
		if (ft_strchr(env_var, '\'') && ft_strchr(env_var, '$'))
		{
			sub = ft_substr(env_var, 0, ft_strchr(env_var, '$') - env_var);
			value_env_var = extract_value_env_quotes(env_var, sub, data);
			index->index = ft_strchr(env_var, '$') - env_var;
			index->str = value_env_var;
			free(env_var);
			free(sub);
			return (index);
		}
		else if (ft_strchr(env_var, '$'))
		{
			int i = 0;
	
			if (env_var[0] == '$')
			{
				sub = ft_strdup(get_env(env_var + 1, data));
				index->index = ft_strlen(env_var);
				index->str = sub;
				free(env_var);
				return (index);
			}
			index->index = 0;
			while (env_var[index->index] && env_var[index->index] != '$')
				index->index++;
			sub = substring(env_var, 0, index->index);
			while (str[i] && str[i] == '"')
				i++;
			index->index += i;
			index->str = sub;
			free(env_var);
			return (index);
		}
		index->str = env_var;
		return (index);
	}
	return (index);
}

static int adjust_position(char *str)
{
	int		i;
	int		len;
	
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
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
	}
	return (i);
}

char	*get_environment_variation_expansion(int i, char ***matrix, t_data *data)
{
	int		len;
	int		pos;
	char	*join;
	t_index_str	*value_env;

	pos = 0;
	join = NULL;
	len = ft_strlen((*matrix)[i]);
	while (pos < len - 1)
	{

		value_env = extract_value_env((*matrix)[i] + pos, data);	
		if (value_env->str)
		{
			// ft_printf("[%s] (%i %i) (%i)\n", value_env->str, value_env->index, ft_strlen(value_env->str), value_env->str[0]);
			if (join == NULL)
			{
				pos += value_env->index;
				join = value_env->str;
			}
			else
			{
				pos += value_env->index;
				join = ft_strjoin_free(join, value_env->str);
				free(value_env->str);
			}
		}
		else
		{
			if (join == NULL)
				join = ft_charjoin(NULL, (*matrix)[i][pos]);
			else
				join = ft_charjoin_free(join, (*matrix)[i][pos]);
			pos++;
		}
	}
	// free(value_env->str);
	free(value_env);
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
		if (i > 0 && ft_strchr((*matrix)[i], '$'))
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

///////////

int	main(int ac, char **av, char **envp)
{
	int		i; // ->nao usas
	t_data	data;
	char	**matrix;

	i = 0;  // ->nao usas
	matrix = NULL;
	init_data(&data);

	data.envp = get_all_environment(envp);
	ft_printf("envp: %s\n", get_env("?", &data));
	matrix = split_2("echo:\"\"\"teste de \"algo\" $? + $? estranho $HOME\"\"\"", ':');
	environment_variation_expansion(&matrix, &data);
	// printf("\n\n\n");
	while (matrix[i])
	{
		printf("(%s)\n", matrix[i]);
		i++;
	}
	free_matrix(matrix);
	free_data(&data);
	return (0);
}
