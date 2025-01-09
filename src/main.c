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

void	split_redirect_between_file_and_content(t_new_list *aux, t_data *data)
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

/* DEPOIS DE CADA (>, <, >>, <<, <>) REDIRECIONAMENTO FUNCIONAR SOZINHO ESTUDAR OS REDIRECIONAMENTO COMHINADO */
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

void	master(char *command, t_data *data)
{
	int			i;
	t_new_list	*aux;
	int			value_redirection;

	if (count_chr('\'', command) % 2 != 0 || count_chr('"', command) % 2 != 0)
	{
		ft_putstr("unclosed quotes\n", 2);
		return ;
	}
	value_redirection = is_redirection(command);
	insert_data(data, command);
	aux = data->list;
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
