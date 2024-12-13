/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:55:19 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/02 11:27:20 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/* CTRL-C */

void	handle_sigint(int sig)
{
	(void)sig;
	write (STDOUT_FILENO, "\nMinishell> ", 12);
}

/* CTRL-\ */

void	setup_signal()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
int main() {
    char input[256];

    // Configura os manipuladores de sinais
    setup_signal();

    while (1) {
        // Exibe o prompt do shell
        write(STDOUT_FILENO, "MiniShell> ", 11);

        // Lê a entrada do usuário
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Se fgets retornar NULL, pode ser CTRL-D (EOF)
            write(STDOUT_FILENO, "Saindo do MiniShell...\n", 23);
            break;
        }

        // Processa o comando (aqui só imprimimos o que foi digitado)
        printf("Você digitou: %s", input);
    }

    return 0;
}
