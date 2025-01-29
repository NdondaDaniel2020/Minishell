/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(const char *file, int mode)
{
	int	fd;

	fd = open(file, mode, 0644);
	if (fd == -1)
	{
		ft_putstr_fd((char *)file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}

void	setup_redir(int fd, int fd_target)
{
	if (dup2(fd, fd_target) < 0)
	{
		close (fd);
		exit (EXIT_FAILURE);
	}
	close (fd);
}

void	init_red_fd(t_red_fd *red_fd)
{
	red_fd->fd = -1;
	red_fd->status = 0;
	red_fd->first_fd = -1;
	red_fd->fd_target = -1;
}
