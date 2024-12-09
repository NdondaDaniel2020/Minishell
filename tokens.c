/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:21:15 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/06 13:22:48 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>

void	prompt()
{
	printf("minishell> ");
	fflush(stdout);
}

char	*read_input()
{
	char	*line;
	size_t	size;

	line = NULL;
	size = 0;

	if (getline(&line, &size, stdin) == -1)
	{
		free(line);
		return (NULL);
	}
	line[strcspn(line, "\n")] = '\0';
	return (line);
}

char	**tokenizar(const char *input)
{
	char	**tokens;
	int	i;
	char	*copy;
	char	*token;

	tokens = malloc(256 * sizeof(char *));
	copy = strdup(input);
	token = strtok(copy, " ");

	while (token != NULL)
	{
		tokens[i++] = strdup(token);
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	free(copy);
	return (tokens);
}

int	sintaxe(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0)
		{
			if (tokens[i + 1] == NULL)
				return (0);
		}
		i++;
	}
	return (1);
}

void exe_command(char **tokens) 
{
   int fd_in = -1; // Para redirecionamento de entrada

    // Processar tokens para redirecionamentos
    for (int i = 0; tokens[i] != NULL; i++) {
        if (strcmp(tokens[i], "<") == 0) {
            fd_in = open(tokens[i + 1], O_RDONLY);
            if (fd_in < 0) {
                perror("Erro ao abrir arquivo de entrada");
                return;
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
            tokens[i] = NULL; // Finalizar a lista de argumentos
            break;
        }
    }

    pid_t pid = fork();
    if (pid == 0) {
        execvp(tokens[0], tokens); // Executa o comando sem redirecionamento
        perror("Erro ao executar comando");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("Erro ao criar processo");
    }
}

int	main()
{
	char	*input;
	char	**tokens;

	while (1)
	{
		prompt();
		input = read_input();
		if (!input)
		{
			printf("Saindo do Minishell..\n");
			break ;
		}
		if (strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		tokens = tokenizar(input);
		free(input);
		if (!sintaxe(tokens))
		{
			printf("Erro: Sintaxe invalida. \n");
			free(tokens);
			continue ;
		}
		exe_command(tokens);
		free(tokens);
	}
	return (0);
}

		

