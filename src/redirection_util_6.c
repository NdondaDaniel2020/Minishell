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
			if ((pos == 0 && ((pos + 1 < len && str[pos + 1] != list[i][0])
					|| ((pos + 1 < len && str[pos + 1] == list[i][0])
					&& (pos + 2 < len && str[pos + 2] != list[i][0]))))
					|| pos != 0)
				return (len_m + (count_all_redirection(str) * 2) + 1);
		}
		i++;
	}
	return (len_m);
}

static bool	condition_extract(int i, int pos, char *str, char **list)
{
	int	len;

	len = ft_strlen(str);
	return ((pos != 0 && ((pos + 1 < len && str[pos + 1] != list[i][0])
			|| ((pos + 1 < len && str[pos + 1] == list[i][0])
			&& (pos + 2 < len && str[pos + 2] != list[i][0]))))
			|| (pos == 0 && ((pos + 1 < len && str[pos + 1] != list[i][0])
				|| ((pos + 1 < len && str[pos + 1] == list[i][0])
				&& (pos + 2 < len && str[pos + 2] != list[i][0]))))
			|| (pos != 0));
}

static bool	condition_to_add(char *str, bool added)
{
	return (added == false
		&& (count_extract_redirection('<', str) == 0)
		&& (count_extract_redirection('>', str) == 0));
}

static int	new_repartision(int iter, char *str, char **new_content)
{
	int			i;
	int			pos;
	bool		added;
	static char	*list[] = {"<>", ">>", "<<", "<", ">", NULL};

	i = 0;
	added = false;
	while (list[i])
	{
		pos = ft_strnpos(str, list[i], ft_strlen(str));
		if (ft_strncmp(str + pos, list[i], ft_strlen(list[i])) == 0
			&& condition_extract(i, pos, str, list))
		{
			many_redirection(str, new_content, &iter);
			break ;
		}
		else if (condition_to_add(str, added))
		{
			new_content[iter++] = ft_strdup(str);
			added = true;
			break ;
		}
		i++;
	}
	return (iter);
}

char	**reset_the_array_for_redirection(char **content)
{
	int		i;
	int		iter;
	int		len_m;
	char	**new_content;

	i = 0;
	len_m = 0;
	len_m = len_matrix(content);
	while (content[i])
	{
		len_m = str_in_list_redirection(content[i], len_m);
		i++;
	}
	if (len_matrix(content) == len_m)
		return (NULL);
	new_content = (char **)ft_calloc(len_m + 1, sizeof(char *));
	i = 0;
	iter = 0;
	while (content[i])
	{
		iter = new_repartision(iter, content[i], new_content);
		i++;
	}
	return (new_content);
}
