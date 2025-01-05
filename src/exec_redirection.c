/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirection_matrix(int status, t_data *data)
{
	if (data->redirection_matrix != NULL)
	{
		if (status != 0)
		{
			int i = 0;
			while (data->redirection_matrix[i])
			{
				if (!valid_string_condition_for_redirection(
						data->redirection_matrix[i]))
					unlink(data->redirection_matrix[i]);
				i++;
			}
		}
		free_matrix(data->redirection_matrix);
	}
}

static void	handle_redir(t_data *data, t_new_list *aux, int mode, int fd_target)
{
	int	i;
	int	fd;
	int cpy_fd;
	int	status;

	i = 0;
	while (data->redirection_matrix[i])
	{
		if (valid_string_condition_for_redirection(data->redirection_matrix[i])
			== false)
			fd = open_file(data->redirection_matrix[i], mode);
		i++;
	}
	cpy_fd = dup(fd_target);
	setup_redir(fd, fd_target);
	if (ft_strlen(aux->content[0]) == 0)
		status = execute_command(1, aux, data);
	else
		status = execute_command(0, aux, data);
	dup2(cpy_fd, fd_target);
	free_redirection_matrix(status, data);
}

void	output(t_data *data, t_new_list *aux)
{
	handle_redir(data, aux, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
}

void	input(t_data *data, t_new_list *aux)
{
	handle_redir(data, aux, O_RDONLY, STDIN_FILENO);
}

void	output_append(t_data *data, t_new_list *aux)
{
	handle_redir(data, aux, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
}
