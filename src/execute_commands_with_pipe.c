/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_with_pipe.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_fd(t_new_list *aux, t_data *data)
{
	if (aux != data->list)
	{
		dup2(data->cpy_read_pipe_operation, STDIN_FILENO);
		close_fd(&data->cpy_read_pipe_operation);
	}
	if (aux->next != NULL)
	{
		dup2(data->write_pipe_operation, STDOUT_FILENO);
		close_fd(&data->write_pipe_operation);
		close_fd(&data->read_pipe_operation);
	}
}

static void	pass_the_fd(t_new_list *aux, t_data *data)
{
	if (data->cpy_read_pipe_operation != -1)
		close(data->cpy_read_pipe_operation);
	if (aux->next != NULL)
	{
		close(data->write_pipe_operation);
		data->cpy_read_pipe_operation = data->read_pipe_operation;
	}
}

static void	execute_commands(int value_redir, t_new_list *aux, t_data *data)
{
	if (value_redir == 1)
		redirection(aux, data);
	else if (value_redir == 0)
		execute_command(0, aux, data);
}

static void	close_fds(t_data *data)
{
	close_fd(&data->write_pipe_operation);
	close_fd(&data->read_pipe_operation);
	close_fd(&data->cpy_read_pipe_operation);
	close_fd(&data->cpy_read_operation);
	close_fd(&data->cpy_write_operation);
}

void	execute_commands_with_pipe(t_data *data)
{
	pid_t		pid;
	t_new_list	*aux;

	aux = data->list;
	data->cpy_read_operation = dup(STDIN_FILENO);
	data->cpy_write_operation = dup(STDOUT_FILENO);
	while (aux)
	{
		if (aux->next != NULL)
			create_pipe(data);
		pid = fork();
		if (pid == 0)
		{
			change_fd(aux, data);
			execute_commands(new_is_redirection(aux->content), aux, data);
			exit(EXIT_SUCCESS);
		}
		else
			pass_the_fd(aux, data);
		aux = aux->next;
	}
	wait_for_children();
	close_fds(data);
}
