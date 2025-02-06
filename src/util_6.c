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

bool	if_heredoc_redirection_exist(t_data *data)
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

bool	is_heredoc_redirection(t_data *data)
{
	int			i;
	int			save;
	t_new_list	*aux;
	t_new_list	*aux_2;

	if (if_heredoc_redirection_exist(data) == false)
		return (false);
	save = -1;
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
				save = i;
				aux_2 = aux;
			}
			i++;
		}
		aux = aux->next;
	}
	////////////////////////////////////////////////////////////////////
	if (save != -1)
	{
		int		i;
		char	*line;

		i = 0;
		line = ft_strnstr(aux_2->content[save], "<<", ft_strlen(aux_2->content[save]));

		if ((line + 2))
		ft_printf("[%s]\n", line);
		
	}
	exit(0);
	return (false);
}
