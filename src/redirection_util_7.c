/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_7.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pos_redirection(const char *big, const char *little, size_t len, int index)
{
	size_t	i;
	size_t	l_lit;

	i = 0;
	l_lit = ft_strlen(little);
	if ((len == 0 && !little) || big == little || l_lit == 0)
		return (-1);
	while (i < len)
	{
		if (l_lit == 1 && big[i] == little[0]
			&& (big[i - 1] != '>' && big[i - 1] != '<')
			&& (big[i + 1] != '>' && big[i + 1] != '<') && --index == 0)
			return (i);
		else if (l_lit == 2 && big[i] == little[0] && big[i + 1] == little[1]
			&& (big[i - 1] != '>' && big[i - 1] != '<')
			&& (big[i + 2] != '>' && big[i + 2] != '<') && --index == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	firts_str(int i, char *str, char **new_content, t_index **indexsing)
{
	int	pos;
	int	start;

	start = len_matrix(new_content);
	pos = pos_redirection(str, indexsing[i]->content->string,
		ft_strlen(str), indexsing[i]->index);
	if (pos != 0)
	{
		new_content[start++] = substring(str, 0, pos);
		new_content[start++] = ft_strdup(indexsing[i]->content->string);
		return (2);
	}
	else
	{
		new_content[start++] = ft_strdup(indexsing[i]->content->string);
		return (1);
	}
}

static int	other_str(int i, char *str, char **new_content, t_index **indexsing)
{
	int	pos1;
	int	pos2;
	int	start;

	start = len_matrix(new_content);
	pos1 = pos_redirection(str, indexsing[i - 1]->content->string,
		ft_strlen(str), indexsing[i - 1]->index);
	pos2 = pos_redirection(str, indexsing[i]->content->string,
		ft_strlen(str), indexsing[i]->index);
	new_content[start++] = substring(str, pos1 +
		ft_strlen(indexsing[i - 1]->content->string), pos2);
	new_content[start++] = ft_strdup(indexsing[i]->content->string);
	return (2);
}

static int	last_str(int i, char *str, char **new_content, t_index **indexsing)
{
	int	pos;
	int	start;

	start = len_matrix(new_content);
	pos = pos_redirection(str, indexsing[i - 1]->content->string,
		ft_strlen(str), indexsing[i - 1]->index);
	if ((pos + ft_strlen(indexsing[i - 1]->content->string)) < ft_strlen(str))
	{
		new_content[start++] = substring(str, pos +
			ft_strlen(indexsing[i - 1]->content->string), ft_strlen(str));
		return (1);
	}
	return (0);
}

void	many_redirection(char *str, char **new_content, int *iter)
{
	int		i;
	int		len_m;
	t_index	**indexsing;

	i = 0;
	len_m = count_all_redirection(str);
	indexsing = indexing_matrix(len_m,
		extract_all_redirection_characters(str));
	while (i < len_m)
	{
		if (i == 0)
			(*iter) += firts_str(i, str, new_content, indexsing);
		else
			(*iter) += other_str(i, str, new_content, indexsing);
		i++;
	}
	(*iter) += last_str(i, str, new_content, indexsing);
	free_indexing_matrix(indexsing);
}
