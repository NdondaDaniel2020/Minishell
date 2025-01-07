/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_10.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_index(t_index *index)
{
	index->index = 0;
	index->content = NULL;
}

int	count_all_redirection(char *str)
{
	int			i;
	t_extract	**matrix;

	i = 0;
	matrix = extract_all_redirection_characters(str);
	while (matrix[i])
		i++;
	free_extract_matrix(matrix);
	return (i);
}

char	*substring(const char *str, int start, int end)
{
	int		len;
	char	*sub;

	len = strlen(str);
	if (start > end)
		return (NULL);
	if (start < 0)
		start = 0;
	if (end > len)
		end = len;
	sub = (char *)malloc((end - start + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, str + start, end - start + 1);
	sub[end - start] = '\0';
	return (sub);
}

char	**list_error(void)
{
	static char	*list[] = {"><", ">>>", "<<<", ">><", "<<>",
		"<>>", "<><", ">> ", "<< ", "<> ", "< ", "> ", NULL};

	return (list);
}

bool	all_char_equal_char(char *str, char chr)
{
	if (ft_strlen(str) == 0)
		return (false);
	while (*str)
	{
		if (*str != chr)
			return (false);
		str++;
	}
	return (true);
}
