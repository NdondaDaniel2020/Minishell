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

int	count_word(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		i++;
	return (i);
}

bool	echo_is_empty(t_new_list *aux)
{
	int		i;

	i = count_word(aux->content);
	if (i == 1)
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	return (0);
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
