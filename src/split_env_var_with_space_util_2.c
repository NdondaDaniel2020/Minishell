/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_var_with_space_util_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	validation_quotes(char *string, int *i)
{
	int	end;

	if (string[*i] == '\'')
	{
		end = *i + 1;
		while (string[end] && string[end] != string[*i])
			end++;
		*i = end;
	}
}

static t_index_str	*ini_and_set_index_str(int index)
{
	t_index_str	*str;

	str = (t_index_str *)ft_calloc(1, sizeof(t_index_str));
	str->index = index;
	return (str);
}

int	get_the_string_break_position(int index, char *string, char *string_exp,
	t_data *data)
{
	int			i;
	int			end;
	int			value;
	t_index_str	*str;

	i = 0;
	str = ini_and_set_index_str(index);
	while (string[i])
	{
		validation_quotes(string, &i);
		if (string[i] == '$')
		{
			end = i + 1;
			while (ft_isalpha(string[end]) || string[end] == '_')
				end++;
			str->str = substring(string, i, end);
			value = get_break_position(str, string, string_exp, data);
			if (value != -1)
				return (free(str->str), free(str), value);
			free(str->str);
			i = end - 1;
		}
		i++;
	}
	return (free(str), -1);
}

int	ft_strnpos2(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	l_lit;

	i = 0;
	l_lit = ft_strlen(little);
	if (len == 0 && !little)
		return (-1);
	if (big == little || l_lit == 0)
		return (-1);
	while (*big && i < len)
	{
		c = 0;
		if (*big == little[0])
		{
			while (little[c] == big[c] && little[c] && big[c] && i + c < len)
				c++;
		}
		if (c == l_lit)
			return (i);
		++big;
		i++;
	}
	return (-1);
}
