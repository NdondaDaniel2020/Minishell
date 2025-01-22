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
		close(data->cpy_read_pipe_operation);
	}
	if (aux->next != NULL)
	{
		dup2(data->write_pipe_operation, STDOUT_FILENO);
		close(data->write_pipe_operation);
		close(data->read_pipe_operation);
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

static void	execute_commands(int value_redirection, t_new_list *aux,
	t_data *data)
{
	if (value_redirection == 1)
		redirection(aux, data);
	else if (value_redirection == 0)
		execute_command(0, aux, data);
}

static void	close_fds(t_data *data)
{
	if (data->write_pipe_operation != -1)
		close(data->write_pipe_operation);
	if (data->read_pipe_operation != -1)
		close(data->read_pipe_operation);
	if (data->cpy_read_pipe_operation != -1)
		close(data->cpy_read_pipe_operation);
}

void	execute_commands_with_pipe(int value_redirection, t_data *data)
{
	pid_t		pid;
	int			pipefd[2];
	t_new_list	*aux;

	data->cpy_read_operation = dup(STDIN_FILENO);
	data->cpy_write_operation = dup(STDOUT_FILENO);
	aux = data->list;
	while (aux)
	{
		if (aux->next != NULL)
		{	
			pipe(pipefd);
			data->write_pipe_operation = pipefd[1];
			data->read_pipe_operation = pipefd[0];
		}
		pid = fork();
		if (pid == 0)
		{
			change_fd(aux, data);

			execute_commands(value_redirection, aux, data);

			dup2(data->cpy_write_operation, STDOUT_FILENO);
			close(data->cpy_write_operation);
			dup2(data->cpy_read_operation, STDIN_FILENO);
			close(data->cpy_read_operation);
			
			exit(0);
		}
		else
		{
			pass_the_fd(aux, data);
			wait(NULL);
		}
		aux = aux->next;
	}
	close_fds(data);
}
