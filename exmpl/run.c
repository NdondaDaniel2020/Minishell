
#include "run.h"

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

int main0(void)
{
	int		new_fd;
    int		pipefd[2];
    pid_t	pid;
    char	buffer[2000]; // Buffer para armazenar a mensagem recebida

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
		execlp("ls", "ls", NULL);
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

int mainia()
{
	int			pipefd[2];
	int			prev_pipefd[2];
	pid_t		pid;
	t_data		data;
	t_new_list	*aux;

	aux = data.list;	
	while (aux)
	{
		// input = readline("TeamWork> ");
		if (aux->next != NULL)
		{
			// Cria um novo pipe
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		// Código do processo filho
		pid = fork();
		if (pid == 0)
		{
			if (aux->next != NULL)
			{
				// Redireciona a saída do comando atual para o pipe
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
				close(pipefd[0]);
			}

			if (aux != data.list)
			{
				// Redireciona a entrada do comando atual para o pipe anterior
				dup2(prev_pipefd[0], STDIN_FILENO);
				close(prev_pipefd[0]);
				close(prev_pipefd[1]);
			}

			if (aux->content[1] == NULL)
				execlp(aux->content[0], aux->content[0], NULL);
			else if (aux->content[2] == NULL)
				execlp(aux->content[0], aux->content[0], aux->content[1], NULL);
			perror("execlp");
			exit(EXIT_FAILURE);
		}
		else
		{
			// Código do processo pai
			if (aux != data.list)
			{
				close(prev_pipefd[0]);
				close(prev_pipefd[1]);
			}

			if (aux->next != NULL)
			{
				prev_pipefd[0] = pipefd[0];
				prev_pipefd[1] = pipefd[1];
			}

			wait(NULL);
		}
		aux = aux->next;
	}
	/**/
	return 0;
}

void	master(char *command, t_data *data)
{
	int			i;
	t_new_list	*aux;

	insert_data(data, command);
	aux = data->list;
	while (aux)
	{
		i = 0;
		while (aux->content[i])
		{
			ft_printf("%s", aux->content[i]);
			i++;
		}
		ft_printf("\n");
		aux = aux->next;
	}
}

int	main(void)
{
	t_data	data;
	char	*input;

	init_data(&data);
	data.envp = get_all_environment();
	data.path = ft_split(get_env("PATH", &data), ':');
	while (1)
	{
		input = readline("TeamWork> ");
		if (input == NULL)
		{
			free_data(&data);
			exit(0);
		}
		else if (input[0] != '\0')
		{
			add_history(input);
			master(input, &data);
			free(input);
		}
	}
	return (0);
}
