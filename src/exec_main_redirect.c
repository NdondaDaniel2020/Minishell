/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	simple_redirect_exec(int fd, int fd_target, t_data *data,
	t_new_list *aux)
{
	int	cpy_fd;
	int	status;

	cpy_fd = dup(fd_target);
	setup_redir(fd, fd_target);
	if (ft_strlen(aux->content[0]) == 0)
		status = execute_command(1, aux, data);
	else
		status = execute_command(0, aux, data);
	dup2(cpy_fd, fd_target);
	close(cpy_fd);
	return (status);
}

static int	double_redirect_exec(int fd, int first_fd, t_data *data,
	t_new_list *aux)
{
	int	status;
	int	cpy_fd;
	int	first_cpy_fd;

	first_cpy_fd = dup(STDIN_FILENO);
	setup_redir(first_fd, STDIN_FILENO);
	cpy_fd = dup(STDOUT_FILENO);
	setup_redir(fd, STDOUT_FILENO);

	if (ft_strlen(aux->content[0]) == 0)
		status = execute_command(1, aux, data);
	else
		status = execute_command(0, aux, data);

	dup2(cpy_fd, STDOUT_FILENO);
	close(cpy_fd);
	dup2(first_cpy_fd, STDIN_FILENO);
	close(first_cpy_fd);
	return (status);
}

void	redirect_main_execution(t_red_fd *red_fd, t_data *data, t_new_list *aux)
{
	if (len_matrix(aux->content) > 0)
	{
		if (red_fd->first_fd == -1)
			red_fd->status = simple_redirect_exec(red_fd->fd,
					red_fd->fd_target, data, aux);
		else
			red_fd->status = double_redirect_exec(red_fd->fd,
					red_fd->first_fd, data, aux);
	}
	else
	{
		red_fd->status = 0;
		close(red_fd->fd);
	}
}
