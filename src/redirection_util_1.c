/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_redirection(char *str, const char *chr)
{
	int		len_n;
	char	**new_content;
	char	**aux_content;

	aux_content = ft_split(str, chr[0]);
	len_n = len_matrix(aux_content);
	new_content = (char **)ft_calloc(len_n + 2, sizeof(char *));
	if (len_n == 1 && str[0] == chr[0])
	{
		new_content[0] = ft_strdup(chr);
		new_content[1] = ft_strdup(aux_content[0]);
	}
	else if (len_n == 1)
	{
		new_content[0] = ft_strdup(aux_content[0]);
		new_content[1] = ft_strdup(chr);
	}
	if (len_n == 2)
	{
		new_content[0] = ft_strdup(aux_content[0]);
		new_content[1] = ft_strdup(chr);
		new_content[2] = ft_strdup(aux_content[1]);
	}
	free_matrix(aux_content);
	return (new_content);
}

static bool	invalid_string_condition_for_redirection(char *str)
{
	return (((count_chr('>', str) == 1) && (ft_strchr(str, '>') 
			&& check_valid_redirection(get_position_chr('>', str), str)))
		 || ((count_chr('<', str) == 1) && (ft_strchr(str, '<')
		 	&& check_valid_redirection(get_position_chr('<', str), str)))
		 || ((count_chr('<', str) == 2
		 	&& check_valid_redirection(get_position_chr('<', str), str)))
		 || ((count_chr('>', str) == 2
		 	&& check_valid_redirection(get_position_chr('>', str), str))));
}

static char	**join_comands(int len_m, int pos, char **matrix, char **split_cont)
{
	int		i1 = 0;
	int		i2 = 0;
	int		iter = 0;
	char	**new_content;

	new_content = (char **)ft_calloc(len_m + len_matrix(split_cont), sizeof(char *));
	while (matrix[i1] && iter < (len_m + len_matrix(split_cont)))
	{
		if (iter == pos)
		{
			while (split_cont[i2])
				new_content[iter++] = split_cont[i2++];
			i1++;
		}
		else
			new_content[iter++] = ft_strdup(matrix[i1++]);
	}
	free(split_cont);
	return (new_content);
}

static bool	condition_redirection(bool *valid, char *str, char ***split_cont)
{
	if (valid_string_condition_for_redirection(str))
	{
		(*valid) = true;
		return (true);
	}
	if (invalid_string_condition_for_redirection(str))
	{
		if (ft_strchr(str, '>') && count_chr('>', str) == 2)
			(*split_cont) = split_redirection(str, ">>");
		else if (ft_strchr(str, '<') && count_chr('<', str) == 2)
			(*split_cont) = split_redirection(str, "<<");
		else if (ft_strchr(str, '>') && count_chr('>', str) == 1)
			(*split_cont) = split_redirection(str, ">");
		else if (ft_strchr(str, '<') && count_chr('<', str) == 1)
			(*split_cont) = split_redirection(str, "<");
		return (true);
	}
	return (false);
}

char	**reset_the_array_for_redirection(char **matrix)
{
    int		pos;
    int		iter;
    int		len_m;
    bool	valid;
    char	**split_cont;

    pos = -1;
    iter = 0;
    valid = false;
    split_cont = NULL;
    len_m = len_matrix(matrix);
    while (matrix[iter])
    {
        if (condition_redirection(&valid, matrix[iter], &split_cont))
        {
            pos = iter;
            break ;
        }
        iter++;
    }
    if (valid == false && split_cont)
		return (join_comands(len_m, pos, matrix, split_cont));
	return (NULL);
}
