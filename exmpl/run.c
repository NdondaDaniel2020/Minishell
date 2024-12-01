
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

typedef struct s_data
{
	bool	space;
	bool	automatic_input;
	char	*command;
	char	*output;
	char	*put_amb;
	char	**path;
	char	**envp;
	// t_btree	*btree;
	int		write_on_the_pipe;
	int		read_in_the_pipe;
}			t_data;

int mai()
{
    // Abre o arquivo no modo de escrita
    int fd;
	int pid;
	int new_fd;

	fd = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	new_fd = dup(STDOUT_FILENO);

	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execlp("ls", "ls", "-l", NULL);
	}
	else
	{
		waitpid(pid, NULL, 0);
		dup2(new_fd, STDOUT_FILENO);
		close(new_fd);
		unlink("saida.txt");
		execlp("ls", "ls", "-l", NULL);
	}
    return 1;
}

int maina()
{
    int pipefd[2]; // Array para armazenar os descritores do pipe (0 para leitura, 1 para escrita)
    pid_t pid;
    char buffer[2000]; // Buffer para armazenar a mensagem recebida

   	int new_fd;


    pipe(pipefd);
	new_fd = dup(STDOUT_FILENO);

    pid = fork();
    if (pid < 0)
	{
        perror("Erro ao criar o processo filho");
        return 1;
    }
	else if (pid == 0)
	{
        // Código do processo filho
        close(pipefd[0]); // Fecha a extremidade de leitura do pipe no processo filho

		dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
		execlp("ls", "ls", "-l", NULL);
        return (0);
    }
	else
	{
        // Código do processo pai
        close(pipefd[1]);

        // Espera que o processo filho termine
        wait(NULL);

        // Lê a mensagem enviada pelo processo filho
        read(pipefd[0], buffer, sizeof(buffer));
        printf("[%s]\n", buffer);
        close(pipefd[0]); // Fecha a extremidade de leitura após a leitura
    }

    return 0;
}

