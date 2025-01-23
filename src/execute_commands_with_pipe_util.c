/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_with_pipe_util.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool	new_is_redirection(char **matix)
{
	int		i;

	i = 0;
	while (matix[i])
	{
		if (valid_string_condition_for_redirection(matix[i]))
			return (true);
		i++;
	}
	return (false);
}

void	create_pipe(t_data *data)
{
	int		pipefd[2];

	pipe(pipefd);
	data->write_pipe_operation = pipefd[1];
	data->read_pipe_operation = pipefd[0];
}
