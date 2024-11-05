#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    char *argv[] = {"/bin/ls", "-l", "/home", NULL}; // Lista de argumentos terminada com NULL
    char *envp[] = {NULL}; // Ambiente para o novo programa

    printf("Executando ls -l /home usando execve\n");

    // Executa o novo programa
    if (execve("/bin/ls", argv, envp) == -1) {
        perror("Erro ao executar execve");
        exit(EXIT_FAILURE);
    }

    // Este código não será executado se execve for bem-sucedido
    printf("Este código não será executado.\n");

    return 0;
}