/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_file_redirection(t_new_list *aux)
{
	int		i;
	int		len;
	bool	valid;

	i = 0;
	len = 0;
	valid = false;
	while (aux->content[i])
	{
		if (valid_string_condition_for_redirection(aux->content[i])
			&& valid == false)
			valid = true;
		if (valid)
			len++;
		i++;
	}
	return (len);
}

static void	split_redirect_between_file_and_content(t_new_list *aux, t_data *data)
{
	int		i;
	int		rm;
	int		len;
	int		len_m;
	bool	valid;

	i = 0;
	rm = 0;
	valid = false;
	len_m = len_matrix(aux->content);
	len = count_file_redirection(aux);
	data->redirection_matrix = ft_calloc(len + 1, sizeof(char *));
	while (i < len_m)
	{
		if (valid_string_condition_for_redirection(aux->content[i]) && !valid)
			valid = true;
		if (valid)
		{
			data->redirection_matrix[rm++] = aux->content[i];
			aux->content[i] = NULL;
		}
		if (valid == false && ft_strlen(aux->content[i]) == 0)
			aux->content[i] = NULL;
		i++;
	}
}

void	redirection(t_new_list *aux, t_data *data)
{
	char	**new_content;

	new_content = reset_the_array_for_redirection(aux->content);
	if (new_content)
	{
		ft_lstnew_addafter_pos(&data->list, data->list,
			ft_lstnew_new(new_content));
		return ;
	}
	if (valid_redirection_syntax(aux))
		return ;
	if (adjust_filename_in_redirection_syntax(aux))
		return ;
	ajust_all_position(&aux->content);
	split_redirect_between_file_and_content(aux, data);
	if (ft_strncmp(data->redirection_matrix[0], ">>", 2) == 0
		|| ft_strncmp(data->redirection_matrix[0], "<>", 2) == 0)
		output_append(data, aux);
	else if (ft_strncmp(data->redirection_matrix[0], "<<", 2) == 0)
		input(data, aux);
	else if (ft_strncmp(data->redirection_matrix[0], "<", 1) == 0)
		input(data, aux);
	else if (ft_strncmp(data->redirection_matrix[0], ">", 1) == 0)
		output(data, aux);
}

////////////////////////////////////////////////////////////////////////////////

void	change_fd(int *aux_pipefd, int pipefd[2], t_new_list *aux, t_data *data)
{
	if (aux != data->list)
	{
		dup2((*aux_pipefd), STDIN_FILENO);
		close((*aux_pipefd));
	}
	if (aux->next != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
}

void	pass_the_fd(int *aux_pipefd, int pipefd[2], t_new_list *aux)
{
	if ((*aux_pipefd) != -1)
		close((*aux_pipefd));
	if (aux->next != NULL)
	{
		close(pipefd[1]);
		(*aux_pipefd) = pipefd[0];
	}
}

////////////////////////////////////////////////////////////////////////////////

void	master(char *command, t_data *data)
{
	int			i;
	t_new_list	*aux;
	int			value_redirection;

	if (simple_error(command))
		return ;
	value_redirection = is_redirection(command);
	insert_data(data, command);
	aux = data->list;
	if (data->is_pipe == false)
	{
		while (aux)
		{
			i = 0;
			if (ft_strlen(aux->content[i]) == 0)
				i++;
			if (value_redirection == 1)
				redirection(aux, data);
			else if (value_redirection == 0)
				execute_command(i, aux, data);
			aux = aux->next;
		}
	}
	else
	{
		pid_t	pid;
		int		pipefd[2];
		int		aux_pipefd;

		while (aux)
		{
			if (aux->next != NULL)
				pipe(pipefd);
			pid = fork();
			if (pid == 0)
			{
				change_fd(&aux_pipefd, pipefd, aux, data);
				if (value_redirection == 1)
					redirection(aux, data);
				else if (value_redirection == 0)
					execute_command(0, aux, data);
				exit(0);
			}
			else
			{
				pass_the_fd(&aux_pipefd, pipefd, aux);
				wait(NULL);
			}
			aux = aux->next;
		}
	}
	free_all_data(data);
}

int	main(void)
{
	t_data	data;
	char	*input;

	setup_signal();
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
