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

static int	count_substrings(char *str, char chr)
{
	int	count;
	int	in_quotes;

	count = 0;
	in_quotes = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			in_quotes = !in_quotes;
		}
		else if (*str == chr && !in_quotes)
		{
			count++;
			while (*str == chr)
				str++;
			continue ;
		}
		str++;
	}
	return (count + 1);
}

static void	init_split(t_split *split, char *str, char chr)
{
	split->len = 0;
	split->in_quotes = 0;
	split->substr_count = count_substrings(str, chr);
	split->result = malloc((split->substr_count + 1) * sizeof(char *));
	split->start = str;
	split->end = str;
}

static void	split_substring(int *i, t_split *split, char chr)
{
	split->len = split->end - split->start;
	split->result[*i] = malloc((split->len + 1) * sizeof(char));
	strncpy(split->result[*i], split->start, split->len);
	split->result[*i][split->len] = '\0';
	(*i)++;
	while (*split->end == chr)
		split->end++;
	split->start = split->end;
}

char	**split_2(char *str, char chr)
{
	int			i;
	t_split		split;

	i = 0;
	init_split(&split, str, chr);
	while (*split.end)
	{
		if (*split.end == '"' || *split.end == '\'')
			split.in_quotes = !split.in_quotes;
		else if (*split.end == chr && !split.in_quotes)
		{
			split_substring(&i, &split, chr);
			continue ;
		}
		split.end++;
	}
	split.result[i] = strdup(split.start);
	split.result[split.substr_count] = NULL;
	return (split.result);
}
