/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 08:58:44 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/02 09:55:58 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

/* Abre o arquivo com o modo e permissões necessarias*/

int	open_file(const char *file, int mode)
{
	int	fd;

	fd = open(file, mode, 0644);
	if (fd < 0)
	{
		perror ("Erro ao abrir arquivo");
		exit (EXIT_FAILURE);
	}
	return (fd);
}

/* configura o redirecionamento para o descritor de arquivo fornecido.*/

void	setup_redir(int fd, int fd_target)
{
	if (dup2(fd, fd_target) < 0)
	{
		perror("Erro ao redirecionar");
		close (fd);
		exit (EXIT_FAILURE);
	}
	close (fd);
}

/* Executa o comando fornecido */

void	exe_command(char *command, int fd, int fd_target)
{
	setup_redir(fd, fd_target);
	
	char *args[] = {"/bin/sh", "-c", command, NULL};
	if (execve("/bin/sh", args, NULL) == -1)
	{
		perror("Erro ao executar o commando");
		exit(EXIT_FAILURE);
	}
}

/* Cria o processo filho, configura o redir e executa o comando*/

void	exec_redir(char *command, int fd, int fd_target)
{
	int	status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Erro ao criar processo filho");
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		exe_command(command, fd, fd_target);
	}
	else
	{
		close(fd);
		wait(&status);
		if (status != 0)
			printf("O comando '%s' falhou com status %d\n", command, status);
	}
}

/* main */

void	handle_redir(char *command, char *file, int mode, int fd_target)
{
	int	fd;

	fd = open_file(file, mode);
	exec_redir(command, fd, fd_target);
}

/* redirections */

void	output(char *command, char *filename)
{
	handle_redir(command, filename, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
}

void	input(char *command, char *infile)
{
	handle_redir(command, infile, O_RDONLY, STDIN_FILENO);
}

void	output_append(char *command, char *outfile)
{
	handle_redir(command, outfile, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
}

/* main just for tests */
other_command(aux, data);
int main() {
    // Redirecionar saída para arquivo >
    output("echo Hello, World!", "outpu.txt");

    // Redirecionar entrada a partir de um arquivo <
    input("cat", "output.txt");

    // Teste com modo de append
    int i = 0;
    while (i <= 10)
    {
		// >>
    	output_append("echo Append Test", "output.txt");
		i++;
	}    

    return 0;
}

