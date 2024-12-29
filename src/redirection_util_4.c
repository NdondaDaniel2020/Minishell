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

static bool	check_extract_lens(t_two_extract *ext, char *str)
{
	init_two_extract(ext);
	ext->len_1 = count_extract_redirection('>', str);
	ext->len_2 = count_extract_redirection('<', str);
	if (ext->len_1 == 0 && ext->len_2 == 0)
		return (true);
	return (false);
}

static void	two_extract(int i, int *end, t_extract **mtx, t_two_extract *ext)
{
	if (ext->ext1->start < ext->ext2->start)
	{
		mtx[i] = ext->ext1;
		(*end) += ext->ext1->returned;
		free(ext->ext2->string);
		free(ext->ext2);
	}
	else
	{
		mtx[i] = ext->ext2;
		(*end) += ext->ext2->returned;
		free(ext->ext1->string);
		free(ext->ext1);
	}
}

static void	extract_redir(int i, int *end, t_extract **mtx, t_two_extract *ext)
{
	if (ext->ext1 && ext->ext1->returned > 0 && ext->ext2 == NULL)
	{
		mtx[i] = ext->ext1;
		(*end) += ext->ext1->returned;
	}
	else if (ext->ext2 && ext->ext2->returned > 0 && ext->ext1 == NULL)
	{
		mtx[i] = ext->ext2;
		(*end) += ext->ext2->returned;
	}
	else if (ext->ext1 && ext->ext2 && ext->ext1->returned > 0
			&& ext->ext2->returned > 0)
		two_extract(i, end, mtx, ext);
}

t_extract	**extract_all_redirection_characters(char *str)
{
	int				i;
	int				end;
	t_two_extract	ext;
	t_extract		**matrix_ext;

	i = 0;
	end = 0;
	if (check_extract_lens(&ext, str))
		return ((t_extract **)(NULL));
	matrix_ext = (t_extract **)ft_calloc(ext.len_1 + ext.len_2 + 1,
		sizeof(t_extract *));
	if (!matrix_ext)
		return ((t_extract **)(NULL));
	while (i < (ext.len_1 + ext.len_2))
	{
		ext.ext1 = extract_redirection_character('>', str + end);
		ext.ext2 = extract_redirection_character('<', str + end);
		if (ext.ext1 == NULL && ext.ext2 == NULL)
			break ;
		extract_redir(i, &end, matrix_ext, &ext);
		i++;
	}
	return (matrix_ext);
}
