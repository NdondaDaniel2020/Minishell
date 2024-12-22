/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_two_extract(t_two_extract *ext)
{
	ext->len_1 = 0;
	ext->len_2 = 0;
	ext->ext1 = NULL;
	ext->ext2 = NULL;
}

void	init_var_redirection(t_var_red *red)
{
	red->list_error = NULL;
	red->extract_matrix = NULL;
}

void	init_extract(t_extract *extract)
{
	extract->string = NULL;
	extract->start = 0;
	extract->end = 0;
	extract->returned = 0;
}

t_extract	*extract_redirection_character(char chr, char *str)
{
	int			pos;
	char		*str_strim;
	t_extract	*ext;

	ext = (t_extract *)ft_calloc(1, sizeof(t_extract));
	init_extract(ext);
	pos = get_position_chr(chr, str);
	if (pos == -1)
	{
		free(ext);
		return ((t_extract *)NULL);
	}
	while ((str[pos + ext->end] == ' ') || (str[pos + ext->end] == '>')
		|| (str[pos + ext->end] == '<'))
		ext->end++;
	str_strim = ft_substr(str, pos, ext->end);
	ext->string = ft_strtrim(str_strim, " ");
	ext->start = pos;
	ext->returned = pos + ext->end;
	free(str_strim);
	return (ext);
}

void	free_extract_matrix(t_extract **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]->string);
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
