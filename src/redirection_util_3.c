/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_3.c                               :+:      :+:    :+:   */
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

static void	change_position(int pos, int len, char ***matrix)
{
	char	**auxm;

	auxm = (char **)ft_calloc(3 , sizeof(char *));
	auxm[0] = (*matrix)[pos];
	auxm[1] = (*matrix)[pos + 1];
	while (pos < len - 2)
	{
		(*matrix)[pos] = (*matrix)[pos + 2];
		pos++;
	}
	(*matrix)[len - 2] = auxm[0];
	(*matrix)[len - 1] = auxm[1];
	free(auxm);
}

void	ajust_position(char ***matrix)
{
	int		i;
	int		len;
	int		pos;

	i = 0;
	pos = -1;
	len = len_matrix((*matrix));
	while ((*matrix)[i])
	{
		if (valid_string_condition_for_redirection((*matrix)[i]))
		{
			pos = i;
			break ;
		}
		i++;
	}
    if (pos != -1 && pos < len - 1)
		change_position(pos, len, matrix);
}
