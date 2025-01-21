/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_new_list *aux, t_data *data)
{
	int		i1;
	int		i2;

	if (echo_is_empty(aux))
		return (change_environment_variables_question_mark(0, data));
	i1 = 0;
	while (!ft_strncmp(aux->content[i1], "echo", ft_strlen(aux->content[i1])))
		i1++;
	traverse_n(&i1, data);
	while (aux->content[i1])
	{
		i2 = 0;
		while (aux->content[i1][i2])
		{
			ft_putchar_fd(aux->content[i1][i2], 1);
			i2++;
		}
		if (aux->content[i1 + 1] && data->space)
			ft_putchar_fd(' ', 1);
		i1++;
	}
	add_bar_n(aux);
	return (change_environment_variables_question_mark(0, data));
}
