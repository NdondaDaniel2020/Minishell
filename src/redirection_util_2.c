/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	condition_add_more_one(int i, char ***matrix)
{
	return ((*matrix)[i] != NULL
		&& (all_char_equal_char((*matrix)[i], '"')
			|| all_char_equal_char((*matrix)[i], '\'')));
}

static int	last_adjust(int len, char **end, char **start, char ***matrix)
{
	int	i;
	int	e;
	int	s;

	i = 0;
	e = 0;
	s = 0;
	if (start == NULL || *start == NULL || matrix == NULL || *matrix == NULL)
	{
		if (*start != NULL || start != NULL)
			free(start);
		return (free(end), 1);	
	}
	while (i < len)
	{
		if (i < len_matrix(start))
			(*matrix)[i++] = start[s++];
		else
			(*matrix)[i++] = end[e++];
	}
	return (free(end), free(start), 0);
}

void	ajust_all_position(char ***matrix)
{
	int		i;
	int		e;
	int		s;
	char	**end;
	char	**start;

	i = 0;
	e = 0;
	s = 0;
	end = (char **)ft_calloc(len_matrix((*matrix)) + 1, sizeof(char *));
	start = (char **)ft_calloc(len_matrix((*matrix)) + 1, sizeof(char *));
	while (i < len_matrix((*matrix)))
	{
		if (valid_string_condition_for_redirection((*matrix)[i]))
		{
			end[e++] = (*matrix)[i++];
			if ((*matrix)[i] != NULL)
				end[e++] = (*matrix)[i++];
			if (condition_add_more_one(i, matrix))
				end[e++] = (*matrix)[i++];
		}
		else
			start[s++] = (*matrix)[i++];
	}
	last_adjust(len_matrix((*matrix)), end, start, matrix);
}

int	count_extract_redirection(char chr, char *str)
{
	int			i;
	int			end;
	int			len;
	t_extract	*ext;

	i = 0;
	end = 0;
	len = ft_strlen(str);
	while (end < len)
	{
		ext = extract_redirection_character(chr, str + end);
		if (ext == NULL)
			break ;
		end += ext->returned;
		free(ext->string);
		free(ext);
		i++;
	}
	return (i);
}
