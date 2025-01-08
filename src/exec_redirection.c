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
	}
}

static void	handle_redir(t_data *data, t_new_list *aux, int fd_target)
{
	int	i;
	int	fd;
	int	len_m;
	int	cpy_fd;
	int	status;
	int	first_fd;
	int	first_cpy_fd;

	i = 0;
	fd = -1;
	first_fd = -1;
	len_m = len_matrix(data->redirection_matrix);
	while (data->redirection_matrix[i])
	{
		if (ft_strncmp(data->redirection_matrix[i], "<>", 2) == 0)
		{
			/////////////////////////////////////////////////////////////////
			fd = open_file(data->redirection_matrix[i + 1], O_WRONLY | O_CREAT | O_APPEND);
			fd = dup(STDOUT_FILENO);
			/////////////////////////////////////////////////////////////////
		}
		else if (ft_strncmp(data->redirection_matrix[i], ">>", 2) == 0)
		{
			/////////////////////////////////////////////////////////////////
			fd = open_file(data->redirection_matrix[i + 1], O_WRONLY | O_CREAT | O_APPEND);
			if (i + 2 < len_m)
				close(fd);
			/////////////////////////////////////////////////////////////////
		}
		else if (ft_strncmp(data->redirection_matrix[i], "<<", 2) == 0)
		{
			ft_printf("herdoc>\n");
		}
		else if (ft_strncmp(data->redirection_matrix[i], ">", 1) == 0)
		{
			/////////////////////////////////////////////////////////////////
			fd = open_file(data->redirection_matrix[i + 1], O_WRONLY | O_CREAT | O_TRUNC);
			if (i + 2 < len_m)
				close(fd);
			/////////////////////////////////////////////////////////////////
		}
		else if (ft_strncmp(data->redirection_matrix[i], "<", 1) == 0)
		{
			/////////////////////////////////////////////////////////////////
			fd = open_file(data->redirection_matrix[i + 1], O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd(data->redirection_matrix[i + 1], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				change_environment_variables_question_mark(1, data);
				return ;
			}
			if (fd_target == STDIN_FILENO && (i + 2) < len_m
				&& ft_strncmp(data->redirection_matrix[i + 2], "<", 1) != 0)
				first_fd = dup(fd);
			else if (i + 2 < len_m)
				close(fd);
			/////////////////////////////////////////////////////////////////
		}
		i++;
	}
	if (len_matrix(aux->content) > 0)
	{
		if (first_fd == -1)
		{
			// caso de execucao de redirecionamento simples
			///////////////////////////////////////////
			cpy_fd = dup(fd_target);
			setup_redir(fd, fd_target);
			if (ft_strlen(aux->content[0]) == 0)
				status = execute_command(1, aux, data);
			else
				status = execute_command(0, aux, data);
			dup2(cpy_fd, fd_target);
			close(cpy_fd);
			///////////////////////////////////////////
		}
		else
		{
			// caso de execucao de redirecionamento duplo
			///////////////////////////////////////////
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
			///////////////////////////////////////////
		}
	}
	else
	{
		status = 0;
		close(fd);
	}
	free_redirection_matrix(status, data);
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
