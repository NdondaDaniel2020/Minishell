/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_redirect_directions_are_handled_here.c    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	all_redirect_directions_are_handled_here(int i, t_red_fd *red_fd,
	t_data *data)
{
	if (ft_strncmp(data->redirection_matrix[i], "<>", 2) == 0)
		red_fd->fd = left_right_redirection(i, data,
				O_WRONLY | O_CREAT | O_APPEND);
	else if (ft_strncmp(data->redirection_matrix[i], ">>", 2) == 0)
		red_fd->fd = double_right_redirect(i, data,
				O_WRONLY | O_CREAT | O_APPEND);
	else if (ft_strncmp(data->redirection_matrix[i], "<<", 2) == 0)
		red_fd->fd = double_left_redirect(i, data, red_fd);
	else if (ft_strncmp(data->redirection_matrix[i], ">", 1) == 0)
		red_fd->fd = right_redirect(i, data, O_WRONLY | O_CREAT | O_TRUNC);
	else if (ft_strncmp(data->redirection_matrix[i], "<", 1) == 0)
		red_fd->fd = left_redirect(i, data, O_RDONLY, red_fd);
}
