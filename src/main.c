#include "minishell.h"


void execute_command(char *command)
{
	// extrair o comando e retornar uma matriz com os comandos repartido

	// verificar se o comando foi executado com /bin/command
	
	// escolher a execucao
	// if bin
		// executar comando bin
	// else
		// executar o criado

	printf("Executing command: %s\n", command);
}

int main(void)
{
	char *input;

    while (1)
	{
		input = readline("TeamWork> ");
        add_history(input);
        // printf("%s\n", input);
        free(input);
    }
    return 0;
}