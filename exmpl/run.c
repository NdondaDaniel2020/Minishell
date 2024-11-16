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
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/resource.h>

int main() 
{
    char *argv[] = {"clear", NULL};
     char *envp[] = {"TERM=xterm-256color", NULL}; 
    
    // Executa o novo programa
    if (execve("/bin/clear", argv, envp) == -1)
    {
        perror("Erro ao executar execve");
        exit(EXIT_FAILURE);
    }
    // Este código não será executado se execve for bem-sucedido
    printf("Este código não será executado.\n");

    return 0;
}
