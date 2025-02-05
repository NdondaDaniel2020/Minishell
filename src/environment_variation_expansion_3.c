/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variation_expansion_3.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*break_the_content_of_double_quotes(int start, int end, char *env_var,
	t_data *data)
{
	char	*string;
	char	*string_exp;

	string = NULL;
	string_exp = NULL;
	if (start == end && env_var[end - 1] == '$')
	{
		string_exp = ft_strdup("$");
	}
	else if (start != end)
	{
		string = substring(env_var, start, end);
		string_exp = adjustment_in_the_extraction_string(string, data);
		free(string);
	}
	return (string_exp);
}

static void	join_expanded_content_util(char **sub, char **string_exp,
	char **join)
{
	if ((*join) == NULL)
	{
		(*join) = ft_strjoin_free((*sub), (*string_exp));
		free((*string_exp));
	}
	else
	{
		(*join) = ft_strjoin_free((*join), (*sub));
		(*join) = ft_strjoin_free((*join), (*string_exp));
		free((*string_exp));
		free((*sub));
	}
}

void	join_expanded_content(char **sub, char **string_exp, char **join)
{
	if ((*sub) == NULL && (*string_exp))
	{
		if ((*join) == NULL)
			(*join) = ft_strdup((*string_exp));
		else
			(*join) = ft_strjoin_free((*join), (*string_exp));
		free((*string_exp));
	}
	else if ((*sub) && (*string_exp))
		join_expanded_content_util(sub, string_exp, join);
	else
	{
		(*join) = ft_strjoin_free((*join), (*sub));
		free((*sub));
	}
}

char	*expand_double_quote_content(char *env_var, t_index_str *index,
	t_data *data)
{
	int		end;
	int		start;
	char	*sub;
	char	*join;
	char	*string_exp;

	end = 0;
	start = 0;
	join = NULL;
	while (end < (int)ft_strlen(env_var) && env_var[end])
	{
		sub = NULL;
		string_exp = NULL;
		sub = get_sub(env_var, &end);
		start = end;
		get_the_range_of_the_string(env_var, &end);
		string_exp = break_the_content_of_double_quotes(start, end,
				env_var, data);
		join_expanded_content(&sub, &string_exp, &join);
	}
	index->index++;
	return (free(env_var), join);
}

t_index_str	*exolate_the_content_with_double_quotes(char *str,
	t_index_str *index, t_data *data)
{
	char	*env_var;

	index->index++;
	while (str[index->index] && str[index->index] != '\"')
		index->index++;
	env_var = substring(str, 1, index->index);
	if (ft_strlen(env_var) != 0)
		index->str = expand_double_quote_content(env_var, index, data);
	else
		index->str = env_var;
	return (index);
}
