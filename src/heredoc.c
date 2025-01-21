/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	local_handle_sigint(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

static void	handle_error(char *msg)
{
	ft_putstr_fd("TeamWork: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	handle_heredoc_input(t_data *data, char *delimiter)
{
	char	*line;

	signal(SIGINT, local_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	close(data->read_in_the_pipe);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			put_warning(data->heredoc_line_delimited, delimiter);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		if (ft_strchr(line, '$') || ft_strchr(line, '\'')
			|| ft_strchr(line, '"'))
			environment_variation_expansion_in_heredoc(&line, data);
		write(data->write_on_the_pipe, line, ft_strlen(line));
		write(data->write_on_the_pipe, "\n", 1);
		free(line);
	}
	free(line);
	close(data->write_on_the_pipe);
	if (line == NULL)
		exit(1);
	exit(0);
}

void	heredoc(t_data *data, char *delimiter)
{
	int		status;
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (handle_error("pipe error"));
	data->read_in_the_pipe = dup(pipefd[0]);
	data->write_on_the_pipe = dup(pipefd[1]);
	pid = fork();
	if (pid == -1)
	{
		close(data->read_in_the_pipe);
		close(data->write_on_the_pipe);
		return (handle_error("fork error"));
	}
	if (pid == 0)
		handle_heredoc_input(data, delimiter);
	waitpid(pid, &status, 0);
	if (status != 0)
		data->heredoc_line_delimited++;
	close(pipefd[0]);
	close(pipefd[1]);
	close(data->write_on_the_pipe);
}
