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
	int	i;

	if (data->redirection_matrix != NULL)
	{
		if (status != 0)
		{
			i = 0;
			while (data->redirection_matrix[i])
			{
				if (!valid_string_condition_for_redirection(
						data->redirection_matrix[i]))
					unlink(data->redirection_matrix[i]);
				i++;
			}
		}
		free_matrix(data->redirection_matrix);
		data->redirection_matrix = NULL;
	}
}

static void	handle_redir(t_data *data, t_new_list *aux, int fd_target)
{
	int			i;
	t_red_fd	*red_fd;

	i = 0;
	red_fd = (t_red_fd *)ft_calloc(1, sizeof(t_red_fd));
	init_red_fd(red_fd);
	red_fd->fd_target = fd_target;
	while (data->redirection_matrix[i])
	{
		all_redirect_directions_are_handled_here(i, red_fd, data);
		if (ft_strncmp(data->redirection_matrix[i], "<", 1) == 0
			&& ft_strlen(data->redirection_matrix[i]) == 1 && red_fd->fd == -1)
		{
			no_such_file_or_directory(i, data);
			return ;
		}
		i++;
	}
	redirect_main_execution(red_fd, data, aux);
	free_redirection_matrix(red_fd->status, data);
	free(red_fd);
}

void	output(t_data *data, t_new_list *aux)
{
	handle_redir(data, aux, STDOUT_FILENO);
}

void	input(t_data *data, t_new_list *aux)
{
	handle_redir(data, aux, STDIN_FILENO);
}

void	output_append(t_data *data, t_new_list *aux)
{
	handle_redir(data, aux, STDOUT_FILENO);
}
