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


void	*ft_realloc(void* ptr, size_t original_size, size_t new_size)
{
	void	*new_ptr;

    if (new_size == 0)
	{
        free(ptr);
        return (NULL);
    }
    if (ptr == NULL)
        return (malloc(new_size));
    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return (NULL);
	if (original_size > new_size)
        original_size = new_size;
	ft_memmove(new_ptr, ptr, original_size);
    free(ptr);
    return (new_ptr);
}

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
