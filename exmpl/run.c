
#include <term.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <termios.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>

#include <sys/wait.h>

int get_exit_status(int status)
{
    if (WIFSIGNALED(status))
        
		return ((WTERMSIG(status) + 128) % 256); // Garante que está no intervalo 0-255

    return (WIFSIGNALED(status) % 256); // Garante o intervalo 0-255
}

int main(int ac, char **av)
{
    int i = 0; // Inicializa para evitar valores indefinidos

    if (ac > 1)
    {
        if (ac > 2)
        {
			
            i = atoi(av[2]); // Converte a string para inteiro
            i = (unsigned char)i; // Calcula o código de saída
            printf("[%i]\n", i); // Exibe o código calculado
        }
        if (strncmp(av[1], "exit", strlen(av[1])) == 0)
        {
            printf("exit\n");
            exit (i); // Retorna o valor calculado
        }
    }
    return (0);
}
