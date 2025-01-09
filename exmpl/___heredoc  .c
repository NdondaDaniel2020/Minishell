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

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h> // Para perror se necessário.
# include <sys/wait.h> // Para waitpid.

# define STDERR 2
# define STDIN 0
# define STDOUT 1

// Macros para tipos de redirecionamento.
# define TRUNC 1
# define APPEND 2
# define INPUT 3
# define HEREDOC 4
# define END 5

// Estrutura para tokens.
typedef struct s_token
{
	char			*str;       // Conteúdo do token.
	int				type;      // Tipo do token.
	struct s_token	*next;     // Próximo token na lista.
}	t_token;

// Estrutura principal.
typedef struct s_mini
{
	int		fdin;            // Arquivo de entrada.
	int		fdout;           // Arquivo de saída.
	int		ret;             // Código de retorno do shell.
	int		no_exec;         // Flag para controlar execução.
}	t_mini;

static void	handle_error(t_mini *mini, const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putendl_fd(msg, STDERR);
	mini->ret = 1;
	mini->no_exec = 1;
}

static void	handle_heredoc_input(int pipefd[2], const char *delimiter)
{
	char	*line;

	close(pipefd[0]);
	
	while (1)
	{
		ft_putstr_fd("> ", STDOUT);
		line = get_next_line(STDIN);
		if (!line || ft_strcmp(line, delimiter) == 0)
			break;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	exit(0);
}

void	heredoc(t_mini *mini, t_token *token)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (handle_error(mini, "pipe error"));
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (handle_error(mini, "fork error"));
	}
	if (pid == 0)
		handle_heredoc_input(pipefd, token->str);
	waitpid(pid, NULL, 0);
	close(pipefd[1]);
	close(mini->fdin);
	mini->fdin = pipefd[0];
	if (dup2(mini->fdin, STDIN) == -1)
	{
		close(pipefd[0]);
		return (handle_error(mini, "dup2 error"));
	}
}

void	redir(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	if (is_type(prev, TRUNC))
		redir(mini, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(mini, token, APPEND);
	else if (is_type(prev, INPUT))
		input(mini, token);
	else if (is_type(prev, HEREDOC))
		heredoc(mini, token);
	if (next && is_type(next, END) == 0)
		redir(mini, next->next);
}

