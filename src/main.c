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

int	g_satatus = 0;

void	master(char *command, t_data *data)
{
	int	value_redirection;

	if (has_unclosed_quotes(command))
	{
		if (heredoc_quotes(data, &command) ==  false)
			return ;
	}
	if (simple_error(command))
		return ;
	value_redirection = is_redirection(command);
	insert_data(data, command);
	if (is_pipe_heredoc(command))
	{	
		if (heredoc_pipe_fork(data) == false)
		return ;
	}
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
		g_satatus = 0;
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
		}
	}
	return (0);
}
