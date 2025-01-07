o executar o comando
ex.:mkdir "TEST de algo le deve tirar as aspas ao criar o comando"

algo mis estranha que vi

algem fora do pico da montanha nao consegue ver a imensidao da paizagem do onhecimento.

ve algo muiti muito muito estranho

de algo que vc tem medo

de algo que vc tem medo

change_environment_variables_question_mark(126, data);

static void	handle_redir(t_data *data, t_new_list *aux, int mode, int fd_target)
{
	int	i;
	int	fd;
	int	cpy_fd;
	int	first_fd;
	int	first_cpy_fd;
	int	status;

	i = 0;
	fd = -1;
	first_fd = -1;
	while (data->redirection_matrix[i])
	{
		if (ft_strncmp(data->redirection_matrix[i], ">>", 2) == 0)
		{
			fd = open_file(data->redirection_matrix[i + 1], mode);
		}
		else if (ft_strncmp(data->redirection_matrix[i], "<>", 2) == 0)
			fd = STDOUT_FILENO;
		else if (ft_strncmp(data->redirection_matrix[i], "<<", 2) == 0)
		{
			ft_printf("herdoc %s\n", data->redirection_matrix[i + 1]);
			// fd = open_file(data->redirection_matrix[i], mode);
		}
		else if (ft_strncmp(data->redirection_matrix[i], ">", 1) == 0)
		{
			fd = open_file(data->redirection_matrix[i + 1], mode);
		}
		else if (ft_strncmp(data->redirection_matrix[i], "<", 1) == 0)
		{
			fd = open_file(data->redirection_matrix[i + 1], mode);
			if (fd == -1)
			{
				ft_putstr_fd(data->redirection_matrix[i + 1], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				return ;
			}
			if ((i + 2) < len_matrix(data->redirection_matrix)
				&& ft_strncmp(data->redirection_matrix[i + 2], "<", 1) != 0)
				first_fd = fd;
		}
		i++;
	}

	if (len_matrix(aux->content) > 0)
	{
		if (first_fd == -1)
		{
			cpy_fd = dup(fd_target);
			setup_redir(fd, fd_target);
			if (ft_strlen(aux->content[0]) == 0)
				status = execute_command(1, aux, data);
			else
				status = execute_command(0, aux, data);
			dup2(cpy_fd, fd_target);
			close(cpy_fd);
		}
		else
		{
			ft_printf("[Dentro] \n\n");

			// first_cpy_fd = dup(STDIN_FILENO);
			// setup_redir(first_fd, STDIN_FILENO);

			// cpy_fd = dup(STDOUT_FILENO);
			// setup_redir(fd, STDOUT_FILENO);

			// if (ft_strlen(aux->content[0]) == 0)
			// 	status = execute_command(1, aux, data);
			// else
			// 	status = execute_command(0, aux, data);

			// dup2(cpy_fd, STDOUT_FILENO);
			// close(cpy_fd);

			// dup2(first_cpy_fd, STDIN_FILENO);
			// close(first_cpy_fd);
		}
	}
	else
	{
		status = 0;
		close(fd);
	}
	free_redirection_matrix(status, data);
}
