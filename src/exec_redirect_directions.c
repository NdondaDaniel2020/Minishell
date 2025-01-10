/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_directions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	left_right_redirection(int i, t_data *data, int mode)
{
	int	fd;

	fd = open_file(data->redirection_matrix[i + 1], mode);
	fd = dup(STDOUT_FILENO);
	return (fd);
}

int	double_right_redirect(int i, t_data *data, int mode)
{
	int	fd;
	int	len_m;

	len_m = len_matrix(data->redirection_matrix);
	fd = open_file(data->redirection_matrix[i + 1], mode);
	if (i + 2 < len_m)
		close(fd);
	return (fd);
}

int	double_left_redirect(int i, t_data *data, t_red_fd *red_fd)
{
	int	fd;
	int	len_m;

	len_m = len_matrix(data->redirection_matrix);
	if ((i + 2) < len_m)
	{
		heredoc(data, data->redirection_matrix[i + 1]);
		if (red_fd->first_fd != -1)
			close(red_fd->first_fd);
		red_fd->first_fd = dup(data->read_in_the_pipe);
		close(data->read_in_the_pipe);
		close(data->write_on_the_pipe);
		fd = dup(STDOUT_FILENO);
	}
	else
	{
		heredoc(data, data->redirection_matrix[i + 1]);
		fd = dup(data->read_in_the_pipe);
		close(data->read_in_the_pipe);
		close(data->write_on_the_pipe);
	}
	return (fd);
}

int	right_redirect(int i, t_data *data, int mode)
{
	int	fd;
	int	len_m;

	len_m = len_matrix(data->redirection_matrix);
	fd = open_file(data->redirection_matrix[i + 1], mode);
	if (i + 2 < len_m)
		close(fd);
	return (fd);
}

int	left_redirect(int i, t_data *data, int mode, t_red_fd *red_fd)
{
	int	fd;
	int	len_m;

	len_m = len_matrix(data->redirection_matrix);
	fd = open_file(data->redirection_matrix[i + 1], mode);
	if (fd == -1)
		return (fd);
	if (red_fd->first_fd == STDIN_FILENO && (i + 2) < len_m
		&& ft_strncmp(data->redirection_matrix[i + 2], "<", 1) != 0)
	{
		if (red_fd->first_fd != -1)
			close(red_fd->first_fd);
		red_fd->first_fd = dup(fd);
	}
	else if (i + 2 < len_m)
		close(fd);
	return (fd);
}
