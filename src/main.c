/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tes.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*pegar comando ex: echo -n "ask" -->  echo -n*/
char	*get_command(char *command)
{
	int		i;
	int		j;
	int		c;
	char	*command_geted;

	i = 0;
	j = 0;
	c = 0;
	command_geted = NULL;
	while (command[i] && command[i++] == ' ')
		c++;
	while (command[i] && command[i] != ' ')
		i++;
	if (command[i] == ' ' && command[i + 1] == '-')
	{
		i++;
		while (command[i] && command[i] != ' ')
			i++;
	}
	command_geted = ft_calloc(i + 1, sizeof(char));
	while ((c + j) < i)
	{
		command_geted[j] = command[(j + c)];
		j++;
	}
	return (command_geted);
}

/* percorrer argumento ate onde inicia o arqumento*/
static void scroll_argument(char *command, int *i)
{
	while (command[*i] && command[*i] == ' ')
		(*i)++;
	while (command[*i] && command[*i] != ' ')
		(*i)++;
	if (command[*i] == ' ' && command[*i + 1] == '-')
	{
		(*i)++;
		while (command[*i] && command[*i] != ' ')
			(*i)++;
	}
}

/*pegar argumento ex: echo -n "ask" "test"-->  ask test*/
char	*get_argument(char *command)
{
	int		i;
	int		j;
	int		c;
	char	*arg_geted;

	i = 0;
	arg_geted = NULL;
	scroll_argument(command, &i);
	if (command[i] != '\0')
	{
		i++;
		c = i;
		j = 0;
		while (command[i++])
			j++;
		arg_geted = ft_calloc(j + 1, sizeof(char));
		j = 0;
		while (command[c])
			arg_geted[j++] = command[c++];
	}
	return (arg_geted);
}

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
