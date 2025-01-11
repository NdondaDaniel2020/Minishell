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

static void	change_fd(int *aux_pipefd, int pipefd[2], t_new_list *aux,
	t_data *data)
{
	if (aux != data->list)
	{
		dup2((*aux_pipefd), STDIN_FILENO);
		close((*aux_pipefd));
	}
	if (aux->next != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
}

static void	pass_the_fd(int *aux_pipefd, int pipefd[2], t_new_list *aux)
{
	if ((*aux_pipefd) != -1)
		close((*aux_pipefd));
	if (aux->next != NULL)
	{
		close(pipefd[1]);
		(*aux_pipefd) = pipefd[0];
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

static void	close_fds(int pipefd[2], int aux_pipefd)
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	if (aux_pipefd != -1)
		close(aux_pipefd);
}

void	execute_commands_with_pipe(int value_redirection, t_data *data)
{
	pid_t		pid;
	int			pipefd[2];
	int			aux_pipefd;
	t_new_list	*aux;

	aux = data->list;
	while (aux)
	{
		if (aux->next != NULL)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			change_fd(&aux_pipefd, pipefd, aux, data);
			execute_commands(value_redirection, aux, data);
			exit(0);
		}
		else
		{
			pass_the_fd(&aux_pipefd, pipefd, aux);
			wait(NULL);
		}
		aux = aux->next;
	}
	close_fds(pipefd, aux_pipefd);
}
