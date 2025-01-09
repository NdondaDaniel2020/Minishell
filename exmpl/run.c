/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <cramos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:52:31 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/23 10:03:34 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>

# define STDERR 2
# define STDIN 0
# define STDOUT 1

// Macros para tipos de redirecionamento.
# define TRUNC 1
# define APPEND 2
# define INPUT 3
# define HEREDOC 4
# define END 5

// Estrutura principal.
typedef struct s_mini
{
	int		fdin;
	int		fdout;
}			t_mini;

static void	handle_error(t_mini *mini, char *msg)
{
	(void)mini;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nTeamWork> ", 12);
}

void	setup_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static void	handle_heredoc_input(t_data *data, char *delimiter)
{
	char	*line;

	setup_signal();
	close(data->read_in_the_pipe);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		write(data->write_on_the_pipe, line, ft_strlen(line));
		write(data->write_on_the_pipe, "\n", 1);
		free(line);
	}
	free(line);
	close(data->write_on_the_pipe);
	exit(0);
}

void	heredoc(t_data *data, t_mini *mini, char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (handle_error(mini, "pipe error"));
	data->read_in_the_pipe = dup(pipefd[0]);
	data->write_on_the_pipe = dup(pipefd[1]);
	pid = fork();
	if (pid == -1)
	{
		close(data->read_in_the_pipe);
		close(data->write_on_the_pipe);
		return (handle_error(mini, "fork error"));
	}
	if (pid == 0)
		handle_heredoc_input(data, delimiter);
	waitpid(pid, NULL, 0);
	close(data->write_on_the_pipe);
	close(mini->fdin);
	mini->fdin = data->read_in_the_pipe;
	if (dup2(mini->fdin, STDIN) == -1)
	{
		close(data->read_in_the_pipe);
		return (handle_error(mini, "dup2 error"));
	}
}

int	main(void)
{
	t_data	data;
	t_mini	mini;
	char	*input = NULL;

	mini.fdin = STDIN_FILENO;
	mini.fdout = STDOUT_FILENO;

	init_data(&data);
	heredoc(&data, &mini, "EOF");

	input = get_next_line(data.read_in_the_pipe);
	ft_printf("%s\n", input);
	free(input);
	while (1)
	{
		readline("TeamWork> ");
	}
	close(data.read_in_the_pipe);
	close(data.write_on_the_pipe);
	close(mini.fdin);
	close(mini.fdout);
}
