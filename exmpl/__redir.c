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
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_data
{
	int			write_on_the_pipe;
	int			read_in_the_pipe;
	int			copy_fd;
	bool		is_pipe;
	bool		space;
	bool		automatic_input;
	char		*command;
	char		*output;
	char		*put_amb;
	char		**path;
	char		**envp;
	// t_new_list	*list;
}			t_data;

//////////////// ft_strdup ////////////////
char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*d;

	if (!s)
		return (NULL);
	i = 0;
	len = strlen(s);
	d = malloc((len + 1) * sizeof(char));
	if (!d)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

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

void	exe_command(t_data *data, int fd, int fd_target)
{
	setup_redir(fd, fd_target);

	char *args[] = {"/bin/sh", "-c", data->command, NULL};
	if (execve("/bin/sh", args, NULL) == -1)
	{
		perror("Erro ao executar o commando");
		exit(EXIT_FAILURE);
	}
}

/* Cria o processo filho, configura o redir e executa o comando*/

void	exec_redir(t_data *data, int fd, int fd_target)
{
	int		status;
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
		exe_command(data, fd, fd_target);
	}
	else
	{
		close(fd);
		wait(&status);|
		if (status != 0)
			printf("O comando '%s' falhou com status %d\n", data->command, status);
	}
}

/* main */

void	handle_redir(t_data *data, char *file, int mode, int fd_target)
{
	int	fd;

	fd = open_file(file, mode);

	exec_redir(data, fd, fd_target);
}

/* redirections */

void	output(t_data *data, char *filename)
{
	handle_redir(data, filename, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
}

void	input(t_data *data, char *infile)
{
	handle_redir(data, infile, O_RDONLY, STDIN_FILENO);
}

void	output_append(t_data *data, char *outfile)
{
	handle_redir(data, outfile, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
}


/* main just for tests */
int main()
{
	int i = 0;
	t_data	data;

	data.command = NULL;
	data.command = ft_strdup("echo Hello, World! 1234567890");

    // Redirecionar saída para arquivo >
    output(&data, "test 123/output_2.txt");

    // Redirecionar entrada a partir de um arquivo <
	// if (data.command)
	// {
	// 	free(data.command);
	// 	data.command = NULL;
	// }
	// data.command = ft_strdup("cat");
	// input(&data, "output_1.txt");

    // Teste com modo de append
    // while (i <= 10)
    // {
	// 	// >>
	// 	if (data.command)
	// 	{
	// 		free(data.command);
	// 		data.command = NULL;
	// 	}
	// 	data.command = ft_strdup("echo Hello, World! 1234567890");
    // 	output_append(&data, "output_1.txt");
	// 	i++;
	// }
	// printf("TESTE COM APPEND\n");
    return 0;
}

