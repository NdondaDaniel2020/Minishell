/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_split(char *str, char chr)
{
	int		end;
	int		len;
	char	aux;

	len = 0;
	end = 0;
	while (str[end])
	{
		if (str[end] == '\'' || str[end] == '"')
		{
			aux = str[end++];
			while (str[end] && str[end] != aux)
				end++;
		}
		if (str[end] == chr)
			len++;
		end++;
	}
	return (len + 1);
}

static void	jump_quotes(char *str, int *end)
{
	char	aux;

	if (str[*end] == '\'' || str[*end] == '"')
	{
		aux = str[(*end)++];
		while (str[*end] && str[*end] != aux)
			(*end)++;
	}
}

char	**split(char *str, char chr)
{
	int		i;
	int		end;
	int		start;
	char	**matrix;

	i = 0;
	end = 0;
	start = 0;
	matrix = (char **)ft_calloc(len_split(str, chr) + 1, sizeof(char *));
	while (str[end])
	{
		jump_quotes(str, &end);
		if (str[end] == chr)
		{
			while (str[start] == ' ')
				start++;
			matrix[i++] = substring(str, start, end);
			start = end;
		}
		end++;
	}
	while (str[start] == ' ')
		start++;
	matrix[i] = substring(str, start, end);
	return (matrix);
}
