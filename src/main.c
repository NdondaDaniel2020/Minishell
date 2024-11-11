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

// static  cd src/
void	execute_command(char *command)
{
	t_data	data;

	init_data(&data);
	data.split_cmd = ft_split(command, ' ');

	if (!ft_strncmp(data.split_cmd[0], "cd", ft_strlen(data.split_cmd[0])))
		cd(&data);

	if (!ft_strncmp(data.split_cmd[0], "pwd", ft_strlen(data.split_cmd[0])))
		pwd(&data);

	if (!ft_strncmp(data.split_cmd[0], "exit", ft_strlen(data.split_cmd[0])))
		exit_(&data);

	if (!ft_strncmp(data.split_cmd[0], "echo", ft_strlen(data.split_cmd[0])))
		echo(&data);

	free_all_data(&data);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("TeamWork> ");
		add_history(input);
		if (ft_strlen(input) != 0)
		{
			execute_command(input);
			free(input);
		}
	}
	return (0);
}
