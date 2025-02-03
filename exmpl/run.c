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

/////////////////////////////////

char	*adjustment_in_the_extraction_string(char *str, t_data *data)
{
	char	*aux;
	char	*void_str;

	aux = get_env(str, data);
	if (aux == NULL)
	{
		void_str = ft_calloc(1, sizeof(char));
		void_str[0] = '\0';
		return (void_str);
	}
	return (ft_strdup(aux));
}

/////////////////////////////////

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
	aux = adjustment_in_the_extraction_string(sub_str + 1, data);
	free(sub_str);
	sub_str = ft_strjoin(inv_sub, aux);
	free(aux);
	aux = ft_strjoin_free(sub_str, inv_sub);
	free(inv_sub);
	return (aux);
}

/////////////////////////////////

t_index_str	*extracting_the_value_with_single_quotes(char *str, t_index_str *index, t_data *data)
{
	char	*env_var;
	char	*value_env_var;

	index->index++;
	while (str[index->index] && (ft_isalnum(str[index->index])
		|| str[index->index] == '_' || str[index->index] == '?'))
		index->index++;
	env_var = substring(str, 1, index->index);
	value_env_var = adjustment_in_the_extraction_string(env_var, data);
	index->str = value_env_var;
	return (free(env_var), index);
}

t_index_str	*exolate_the_content(char *str, t_index_str *index)
{
	int 	i;
	char	*env_var;

	i = 0;
	index->index++;
	while (str[index->index] && str[index->index] != '\'')
		index->index++;
	env_var = substring(str, 1, index->index);
	while (str[i] && str[i] == '\'')
		i++;
	index->index += i;
	index->str = env_var;
	return (index);
}

////////////////////////////////

static t_index_str	*exolate_double_and_single_quotes(char *env_var, t_index_str *index, t_data *data)
{
	char	*sub;
	char	*value_env_var;

	sub = ft_substr(env_var, 0, ft_strchr(env_var, '$') - env_var);
	value_env_var = extract_value_env_quotes(env_var, sub, data);
	index->index = ft_strchr(env_var, '$') - env_var;
	index->str = value_env_var;
	free(env_var);
	free(sub);
	return (index);
}

static t_index_str	*exude_content_without_double_quotes(char *str, char *env_var, t_index_str *index, t_data *data)
{
	int 	i;
	char	*sub;

	i = 0;
	if (env_var[0] == '$')
	{
		sub = adjustment_in_the_extraction_string(env_var + 1, data);
		index->index = ft_strlen(env_var);
		index->str = sub;
		while (str[i] && str[i] == '"')
			i++;
		index->index += i;
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

bool	valid_extract(char *str, int index)
{
	int		i;
	char	*str_aux;

	str_aux = ft_substr(str, 0, index + 1);
	i = count_chr('$', str_aux);
	if (i == 1 && str[index] == ' ')
		return (free(str_aux), false);
	return (free(str_aux), true);
}

t_index_str	*exolate_the_content_with_double_quotes(char *str, t_index_str *index, t_data *data)
{
	int 	i;
	char	*env_var;

	i = 0;
	index->index++;
	while (str[index->index] && str[index->index] != '\"'
		 && valid_extract(str, index->index))
		index->index++;
	env_var = substring(str, 1, index->index);
	if (ft_strchr(env_var, '\'') && ft_strchr(env_var, '$'))
		return (exolate_double_and_single_quotes(env_var, index, data));
	else if (ft_strchr(env_var, '$'))
		return (exude_content_without_double_quotes(str, env_var, index, data));
	index->str = env_var;
	while (str[i] && str[i] == '"')
		i++;
	index->index += i;
	return (index);
}

////////////////////////////////

t_index_str	*extract_value_env(char *str, t_data *data)
{
	int			len;
	t_index_str	*index;

	if (!str)
		return (NULL);
	index = ft_calloc(1, sizeof(t_index_str));
	index->index = 0;
	index->str = NULL;
	len = ft_strlen(str);
	if (str[index->index] == '$' && (index->index + 1) < len)
		return (extracting_the_value_with_single_quotes(str, index, data));
	else if (str[index->index] == '\'')
		return (exolate_the_content(str, index));
	else if (str[index->index] == '\"')
		return (exolate_the_content_with_double_quotes(str, index, data));
	return (index);
}

/////////////////////////////////

static void	join_value_env(t_index_str *value_env, char **join, int *pos)
{
	if ((*join) == NULL)
	{
		(*pos) += value_env->index;
		if (ft_strlen(value_env->str) == 0)
		{
			(*pos)--;
			(*join) = ft_charjoin(NULL, 1);
			(*join) = ft_charjoin_free((*join), 1);
		}
		else
			(*join) = value_env->str;
	}
	else
	{
		(*pos) += value_env->index;
		if (ft_strlen(value_env->str) == 0)
		{
			(*join) = ft_charjoin_free((*join), 1);
			(*join) = ft_charjoin_free((*join), 1);
		}
		else
			(*join) = ft_strjoin_free((*join), value_env->str);
		free(value_env->str);
	}
}

char	*get_environment_variation_expansion(char *str, t_data *data)
{
	int			len;
	int			pos;
	char		*join;
	t_index_str	*value_env;

	pos = 0;
	join = NULL;
	len = ft_strlen(str);
	// ft_printf("%i\n", len);
	while (pos < len)
	{
		ft_printf("[%s] [%s] (%i)\n", str, str + pos, pos);
		value_env = extract_value_env(str + pos, data);
		// ft_printf("[%s]\n", value_env->str);
		if (value_env->str)
			join_value_env(value_env, &join, &pos);
		else
		{
			if (join == NULL)
				join = ft_charjoin(NULL, str[pos]);
			else
				join = ft_charjoin_free(join, str[pos]);
			pos++;
		}
		free(value_env);
		// ft_printf(" == [[%i]]\n", pos);
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
		if ((ft_strchr((*matrix)[i], '$') || ft_strchr((*matrix)[i], '\'')
			|| ft_strchr((*matrix)[i], '\"')))
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

/////////////////////////////////

int	main(int ac, char **av, char **envp)
{
	int		i; // ->nao usas
	t_data	data;
	char	**matrix;

	i = 0;  // ->nao usas
	matrix = NULL;
	ft_printf("{{{%c{%i}}}}\n", 1, 1);
	init_data(&data);
	data.envp = get_all_environment(envp);
	matrix = split_2("ls:'-'ls'-'", ':');
	environment_variation_expansion(&matrix, &data);
	printf("\n\n\n");
	while (matrix[i])
	{
		printf("[%s]\n", matrix[i]);
		// int j = 0;
		// while (matrix[i][j])
		// {
		// 	if (matrix[i][j] == 1)
		// 		printf("Delimitador 1 ");
		// 	printf("[%c][%i]\n", matrix[i][j], matrix[i][j]);
		// 	j++;
		// }
		i++;
	}
	free_matrix(matrix);
	free_data(&data);
	return (0);
}

// Vfs1@gmail
