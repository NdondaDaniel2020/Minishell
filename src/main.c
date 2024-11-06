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

char	*get_option(char *command)
{
	int		i;
	int		j;
	int		c;
	bool	status;
	char	*opt_geted;

	i = 0;
	c = 0;
	opt_geted = NULL;
	while (command[i] && command[i] == ' ')
		i++;
	while (command[i] && command[i] != ' ')
		i++;
	while (command[i] && command[i] == ' ')
		i++;
	if (command[i] && command[i] == '-' && command[i + 1])
	{
		j = i;
		status = true;
		while (status)
		{
			while (command[i] && command[i++] != ' ')
				c++;
			if (command[i] && command[i] != '-')
				status = false;
		}
		ft_putnbr_fd(c, 1);
		ft_putchar_fd(' ', 1);
		ft_putchar_fd('\n', 1);
		opt_geted = ft_calloc(c + 1, sizeof(char));
		c = 0;
		while (j < (i - 1))
			opt_geted[c++] = command[j++];
		opt_geted[c] = '\0';
	}
	return (opt_geted);
}

static void	execute_command(char *command)
{
	char	*cmd;
	char	*opt;
	char	*arg;

	/*
		printf("[%s][%s]\n", command, );
		if (ft_strnstr(command, "/bin/", ft_strlen(command)))
	*/
	arg = get_argument(command);
	cmd = get_command(command);
	opt = get_option(command);
	// if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
	// 	printf("[%s][%s]\n", cmd, prm);
	printf("[%s][%s][%s]\n", cmd, opt, arg);
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
