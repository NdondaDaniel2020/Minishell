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

void	ctrl_d(t_data *data)
{
	data->value_output = ft_atoi(get_env("?", data));
	free_data(data);
	exit(data->value_output);
}

int	master(char *command, t_data *data)
{
	int	value_redirection;

	if (has_unclosed_quotes(command))
	{
		ft_putstr_fd("syntax error: unclosed quotes\n", 2);
		return (free(command), free_all_data(data), 1);
	}
	if (simple_error(command))
		return (free(command), free_all_data(data), 1);
	value_redirection = is_redirection(command);
	insert_data(data, command);
	if (is_pipe_heredoc(command))
	{
		ft_putstr_fd("syntax error: unclosed pipe\n", 2);
		return (free_all_data(data), 1);
	}
	if (is_heredoc_redirection(data))
		get_name_for_heredoc_redirection(data);
	if (data->is_pipe == false)
		execute_commands_without_pipe(value_redirection, data);
	else
		execute_commands_with_pipe(data);
	return (free_all_data(data), 0);
}

void	enter_master(char *input, t_data *data)
{
	add_history(input);
	if (all_is_space(input) == false)
		master(input, data);
	else
		free(input);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*input;

	(void)ac, (void)av, setup_signal(), init_data(&data);
	data.envp = get_all_environment(envp);
	data.path = ft_split(get_env("PATH", &data), ':');
	while (1)
	{
		g_satatus = 0;
		input = readline("TeamWork> ");
		if (g_satatus == 2)
			change_environment_variables_question_mark(130, &data);
		if (input == NULL)
			ctrl_d(&data);
		else if (input[0] != '\0')
			enter_master(input, &data);
		else
			free(input);
	}
	return (0);
}
