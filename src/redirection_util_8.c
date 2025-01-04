/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_6.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_indexing_matrix(t_index **indexed)
{
	int	i;

	i = 0;
	if (!indexed)
		return ;
	while (indexed[i])
	{
		if (indexed[i]->content)
		{
			free(indexed[i]->content->string);
			free(indexed[i]->content);
		}
		free(indexed[i]);
		i++;
	}
	free(indexed);
}

static bool	release_in_case_of_error(int i, t_index **indexed)
{
	if (!indexed[i])
	{
		while (i-- > 0)
		{
			free(indexed[i]->content->string);
			free(indexed[i]->content);
			free(indexed[i]);
		}
		free(indexed);
		return (true);
	}
	return (false);
}

static int	get_value_index(int i, t_extract **matrix)
{
	if (ft_strncmp(matrix[i]->string, "<>", 2) == 0)
		return (0);
	else if (ft_strncmp(matrix[i]->string, ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(matrix[i]->string, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(matrix[i]->string, ">", 1) == 0)
		return (3);
	else if (ft_strncmp(matrix[i]->string, "<", 1) == 0)
		return (4);
	return (-1);
}

t_index	**indexing_matrix(int len, t_extract **matrix)
{
	int		i;
	int		vidx;
	int		index[5];
	t_index	**indexed;

	i = 0;
	vidx = 0;
	while (vidx < 5)
		index[vidx++] = 0;
	indexed = (t_index **)ft_calloc(len + 1, sizeof(t_index *));
	if (!indexed)
		return (NULL);
	while (matrix[i])
	{
		indexed[i] = (t_index *)ft_calloc(1, sizeof(t_index));
		if (release_in_case_of_error(i, indexed))
			return (NULL);
		vidx = get_value_index(i, matrix);
		index[vidx]++;
		indexed[i]->index = index[vidx];
		indexed[i]->content = matrix[i];
		i++;
	}
	free(matrix);
	return (indexed);
}
