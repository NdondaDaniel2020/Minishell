/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command(char *command)
{
	t_data	data;

	data.split_cmd = ft_split(command, ' ');
	if (!ft_strncmp(data.split_cmd[0], "echo",
		ft_strlen(data.split_cmd[0])))
		echo(&data);
	else if (!ft_strncmp(data.split_cmd[0], "pwd",
		ft_strlen(data.split_cmd[0])))
		pwd(&data);
	else if (!ft_strncmp(data.split_cmd[0], "cd",
		ft_strlen(data.split_cmd[0])))
		cd(&data);
	else if (!ft_strncmp(data.split_cmd[0], "exit",
		ft_strlen(data.split_cmd[0])))
		exit_(&data);
	// free_matrix(data.split_cmd);
	// free(retrn);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("TeamWork> ");
		add_history(input);
		execute_command(input);
		free(input);
	}
	return (0);
}
