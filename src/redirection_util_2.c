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

bool	valid_string_condition_for_redirection(char *str)
{
	return ((ft_strncmp(str, ">", 1) == 0 && ft_strlen(str) == 1)
		 || (ft_strncmp(str, "<", 1) == 0 && ft_strlen(str) == 1)
		 || (ft_strncmp(str, "<<", 2) == 0 && ft_strlen(str) == 2)
		 || (ft_strncmp(str, ">>", 2) == 0 && ft_strlen(str) == 2));
}

static void	last_adjust(int len, char **end, char **start, char ***matrix)
{
	int	i;
	int	e;
	int	s;

	i = 0;
	e = 0;
	s = 0;
	while (i < len)
	{
		if (i < len_matrix(start))
			(*matrix)[i++] = start[s++];
		else
			(*matrix)[i++] = end[e++];
	}
	free(end);
	free(start);
}

void	ajust_all_position(char ***matrix)
{
	int		i;
	int		e;
	int		s;
	int		len;
	char	**end;
	char	**start;

	i = 0;
	e = 0;
	s = 0;
	len = len_matrix((*matrix));
	end = (char **)ft_calloc(len + 1, sizeof(char *));
	start = (char **)ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		if (valid_string_condition_for_redirection((*matrix)[i]))
		{
			end[e++] = (*matrix)[i++];
			if ((*matrix)[i] != NULL)
				end[e++] = (*matrix)[i++];
		}
		else
			start[s++] = (*matrix)[i++];
	}
	last_adjust(len, end, start, matrix);
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
			break;
		end += ext->returned;
		free(ext->string);
		free(ext);
		i++;
	}
	return (i);
}
