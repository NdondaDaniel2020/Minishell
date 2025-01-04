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

/* Abre o arquivo com o modo e permissões necessarias*/

int	open_file(const char *file, int mode)
{
	int	fd;

	fd = open(file, mode, 0644);
	if (fd < 0)
	{
		exit (EXIT_FAILURE);
	}
	return (fd);
}

/* configura o redirecionamento para o descritor de arquivo fornecido.*/

void	setup_redir(int fd, int fd_target)
{
	if (dup2(fd, fd_target) < 0)
	{
		close (fd);
		exit (EXIT_FAILURE);
	}
	close (fd);
}
