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
	char	*cmd;
	char	*arg;

	/*
		printf("[%s][%s]\n", command, );
		if (ft_strnstr(command, "/bin/", ft_strlen(command)))
	*/
	arg = get_argument(command);
	cmd = get_command(command);
	// if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
	// 	printf("[%s][%s]\n", cmd, prm);
	printf("[%s][%s]\n", cmd, arg);
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
