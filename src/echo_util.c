/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	echo_is_empty(t_new_list *aux)
{
	if (len_matrix(aux->content) == 1)
	{
		ft_putchar_fd('\n', 1);
		return (true);
	}
	return (false);
}

bool	only_valid_n(const char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	add_bar_n(t_new_list *aux)
{
	if (ft_strncmp(aux->content[1], "-n", 2) != 0)
		ft_putchar_fd('\n', 1);
}

void	traverse_n(int *i, t_data *data)
{
	while (data->list->content[*i] && ft_strnstr(data->list->content[*i],
			"-n", ft_strlen(data->list->content[*i])))
		(*i)++;
}
