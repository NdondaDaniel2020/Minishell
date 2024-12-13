/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:34:23 by cramos-c          #+#    #+#             */
/*   Updated: 2024/11/28 11:34:28 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_TOKENS 100

// Função para dividir a entrada em tokens
char **tokenizar(char *entrada) {
    char **tokens = malloc(sizeof(char *) * MAX_TOKENS);
    int i = 0;

    char *token = strtok(entrada, " ");
    while (token != NULL && i < MAX_TOKENS - 1) {
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL; // Finaliza o array de tokens
    return tokens;
}

// Função para executar o comando com redirecionamento
void executar_comando(char **tokens) {
    int fd_in = -1;

    // Processar redirecionamento
    for (int i = 0; tokens[i] != NULL; i++) {
        if (strcmp(tokens[i], "<") == 0) {
            if (tokens[i + 1] == NULL) {
                fprintf(stderr, "Erro: arquivo de entrada não especificado\n");
                return;
            }

            fd_in = open(tokens[i + 1], O_RDONLY);
            if (fd_in < 0) {
                perror("Erro ao abrir arquivo de entrada");
                return;
            }

            // Redirecionar entrada padrão
            if (dup2(fd_in, STDIN_FILENO) < 0) {
                perror("Erro ao redirecionar entrada");
                close(fd_in);
                return;
            }

            close(fd_in);

            // Remover `<` e o arquivo dos tokens
            tokens[i] = NULL;
            break;
        }
    }

    // Criar processo filho
    pid_t pid = fork();
    if (pid == 0) {
        execvp(tokens[0], tokens);
        perror("Erro ao executar comando");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("Erro ao criar processo filho");
    }
}

int main() {
    char entrada[1024];

    while (1) {
        printf("minishell> ");
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            break;
        }

        // Remover o caractere de nova linha
        entrada[strcspn(entrada, "\n")] = '\0';

        if (strlen(entrada) == 0) {
            continue;
        }

        // Tokenizar entrada e executar comando
        char **tokens = tokenizar(entrada);
        executar_comando(tokens);
        free(tokens);
    }

    return 0;
}


