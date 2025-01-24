/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_with_pipe_util.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	new_is_redirection(char **matix)
{
	int	i;

	i = 0;
	while (matix[i])
	{
		if (valid_string_condition_for_redirection(matix[i]))
			return (true);
		i++;
	}
	return (false);
}

void	create_pipe(t_data *data)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("Failed to create pipe");
		exit(EXIT_FAILURE);
	}
	data->write_pipe_operation = pipefd[1];
	data->read_pipe_operation = pipefd[0];
}

void	close_fd(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	wait_for_children(void)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while ((pid) > 0)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
			{
				ft_putstr_fd("Error", 2);
				ft_putnbr_fd(WEXITSTATUS(status), 2);
				ft_putstr_fd("\n", 2);
			}
		}
		else if (WIFSIGNALED(status))
		{
			ft_putstr_fd("Child", 2);
			ft_putnbr_fd(WEXITSTATUS(status), 2);
			ft_putstr_fd("\n", 2);
		}
		pid = wait(&status);
	}
}
