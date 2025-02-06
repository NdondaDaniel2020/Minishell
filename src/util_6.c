/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	if_heredoc_redirection_exist(t_data *data)
{
	int			i;
	t_new_list	*aux;

	aux = data->list;
	while (aux)
	{
		i = 0;
		while (aux->content[i])
		{
			if (ft_strnstr(aux->content[i], "<<", ft_strlen(aux->content[i])))
				return (true);
			i++;
		}
		aux = aux->next;
	}
	return (false);
}

static bool	first_check_heredoc_redirection(int *save, t_new_list **aux_2,
	t_data *data)
{
	int			i;
	t_new_list	*aux;

	aux = data->list;
	while (aux)
	{
		i = 0;
		while (i < len_matrix(aux->content) && aux->content[i])
		{
			if (ft_strncmp(aux->content[i], "<<", 2) == 0
				&& i + 1 < len_matrix(aux->content))
				return (true);
			if (ft_strnstr(aux->content[i], "<<", ft_strlen(aux->content[i])))
			{
				*save = i;
				(*aux_2) = aux;
			}
			i++;
		}
		aux = aux->next;
	}
	return (false);
}

bool	is_heredoc_redirection(t_data *data)
{
	int			i;
	int			save;
	char		*line;
	t_new_list	*aux_2;
	bool		first_heredoc;

	save = -1;
	aux_2 = NULL;
	first_heredoc = false;
	if (if_heredoc_redirection_exist(data) == false)
		return (false);
	first_heredoc = first_check_heredoc_redirection(&save, &aux_2, data);
	if (first_heredoc)
		return (true);
	if (save != -1)
	{
		i = 2;
		line = ft_strnstr(aux_2->content[save],
			"<<", ft_strlen(aux_2->content[save]));
		while ((line + i)[0] == ' ')
			i++;
		
		if ((line + i)[0] == '\0')
			return (false);
		else
			return (true);
	}
	return (false);
}
