/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_without_pipe.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands_without_pipe(int value_redirection, t_data *data)
{
	int			i;
	t_new_list	*aux;

	aux = data->list;
	while (aux)
	{
		i = 0;
		if (ft_strlen(aux->content[i]) == 0)
			i++;
		if (value_redirection == 1)
			redirection(aux, data);
		else if (value_redirection == 0)
			execute_command(i, aux, data);
		aux = aux->next;
	}
}
