/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_6b.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	condition_count_redict(int pos, int len, char chr, char *str)
{
	return ((pos == 0 && ((pos + 1 < len && str[pos + 1] != chr)
			|| ((pos + 1 < len && str[pos + 1] == chr)
			&& (pos + 2 < len && str[pos + 2] != chr))))
			|| pos != 0);
}

int	str_in_list_redirection(char *str, int len_m)
{
	int			i;
	int			len;
	int			pos;
	static char	*list[] = {"<>", ">>", "<<", "<", ">", NULL};

	i = 0;
	len = ft_strlen(str);
	while (list[i])
	{
		pos = ft_strnpos(str, list[i], ft_strlen(str));
		if (ft_strncmp(str + pos, list[i], ft_strlen(list[i])) == 0)
		{
			if (len == 2 && str[0] == '<' && str[1] == '>')
				return (len_m);		
			if (pos != 0 && ((pos + 1 < len && str[pos + 1] != list[i][0])
				|| ((pos + 1 < len && str[pos + 1] == list[i][0])
				&& (pos + 2 < len && str[pos + 2] != list[i][0]))))
				return (len_m + (count_all_redirection(str) * 2) + 1);
			if (condition_count_redict(pos, len, list[i][0], str))
				return (len_m + (count_all_redirection(str) * 2) + 1);
		}
		i++;
	}
	return (len_m);
}
