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

bool	is_pipe_heredoc(char *command)
{
	int	len;

	len = ft_strlen(command);
	if (command[len - 1] == '|')
		return (true);
	while (len > 0 && command[len - 1] == ' ' )
		len--;
	if (command[len - 1] == '|')
		return (true);
	else
		return (false);
}

void	master(char *command, t_data *data)
{
	int			value_redirection;

	if (simple_error(command))
		return ;
	value_redirection = is_redirection(command);
	insert_data(data, command);
	if (is_pipe_heredoc(command))
		heredoc_pipe_fork(data);
	if (data->is_pipe == false)
		execute_commands_without_pipe(value_redirection, data);
	else
		execute_commands_with_pipe(value_redirection, data);
	free_all_data(data);
}

int	main(void)
{
	t_data	data;
	char	*input;

	setup_signal();
	init_data(&data);
	data.envp = get_all_environment();
	data.path = ft_split(get_env("PATH", &data), ':');
	while (1)
	{
		input = readline("TeamWork> ");
		if (input == NULL)
		{
			free_data(&data);
			exit(0);
		}
		else if (input[0] != '\0' && all_is_space(input) == false)
		{
			add_history(input);
			master(input, &data);
			free(input);
		}
	}
	return (0);
}
