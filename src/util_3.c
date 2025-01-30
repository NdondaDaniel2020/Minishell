/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocation_of_environment_variable_with_space(char **cpy_matrix, char **matrix, t_data *data)
{
	int		i;
	char	**new_matrix;

	i = 0;
	(void)data;
	(void)matrix;
	(void)new_matrix;
	while (cpy_matrix[i])
	{
		ft_printf("%i - {%s}", i, matrix[i]);
		ft_printf("[%s]\n", cpy_matrix[i]);
		i++;
	}
	//  free_matrix(new_matrix) free_matrix(matrix)
	return (NULL);
}

char	**dup_matrix(char **matrix)
{
	int		i;
	int		len;
	char	**new_matrix;

	len = len_matrix(matrix);
	new_matrix = (char **)ft_calloc((len + 1), sizeof(char *));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_matrix[i] = strdup(matrix[i]);
		if (!new_matrix[i])
		{
			while (i > 0)
				free(new_matrix[--i]);
			free(new_matrix);
			return (NULL);
		}
		i++;
	}
	new_matrix[len] = NULL;
	return (new_matrix);
}

void	insert_data(t_data *data, char *command)
{
	int		i;
	int		len_m;
	char	**matrix;
	char	**spliting;
	char	**new_matrix;

	i = 0;
	data->command = command;
	spliting = split_2(command, '|');
	len_m = len_matrix(spliting);
	if (len_m > 1)
		data->is_pipe = true;
	else
		data->is_pipe = false;
	while (spliting[i])
	{
		matrix = split_2(spliting[i], ' ');
		matrix_space_position_adjustment(&matrix);
		null_string(&matrix);
		//////////////////////////////////////////////////////////////////////////////////
		new_matrix = dup_matrix(matrix);
		environment_variation_expansion(&matrix, data);
		//////////////////////////////////////////////////////////////////////////////////
		matrix_space_position_adjustment(&new_matrix);
		matrix_space_position_adjustment(&matrix);
		//////////////////////////////////////////////////////////////////////////////////
		// matrix = 
		allocation_of_environment_variable_with_space(new_matrix, matrix, data);
		//////////////////////////////////////////////////////////////////////////////////
		ft_lstnew_addback(&data->list, ft_lstnew_new(matrix));
		free(spliting[i]);
		i++;
	}
	free(spliting);
}

int	execute_command(int i, t_new_list *aux, t_data *data)
{
	int	re;
	int	len;

	re = 0;
	len = ft_strlen(aux->content[i]);
	if (!ft_strncmp(aux->content[i], "exit", len))
		exit_(aux, data);
	else if (!ft_strncmp(aux->content[i], "pwd", len))
		re = pwd(data);
	else if (!ft_strncmp(aux->content[i], "cd", len))
		re = cd(aux, data);
	else if (!ft_strncmp(aux->content[i], "echo", len))
		re = echo(aux, data);
	else if (!ft_strncmp(aux->content[i], "env", len))
		re = env(aux, data);
	else if (!ft_strncmp(aux->content[i], "export", len))
		re = export(aux, data);
	else if (!ft_strncmp(aux->content[i], "unset", len))
		re = unset(data);
	else
		re = other_command(i, aux, data);
	return (re);
}

bool	valid_redirection_syntax(t_new_list *aux)
{
	int	i;
	int	len;

	i = 0;
	len = len_matrix(aux->content);
	if ((valid_string_condition_for_redirection(aux->content[len - 1]))
		|| ((ft_strlen(aux->content[len - 1]) == 0)
			&& valid_string_condition_for_redirection(aux->content[len - 2])))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (true);
	}
	while (aux->content[i])
	{
		if (valid_string_condition_for_redirection(aux->content[i])
			&& is_directory_valid(aux->content[i + 1]))
		{
			ft_putstr_fd(aux->content[i + 1], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	check_pipe_valid(char *command)
{
	int	i;
	int	len_pipe;

	i = 0;
	len_pipe = 0;
	while (command[i])
	{
		if (command[i] == '|')
			len_pipe++;
		if (command[i] != '|' && command[i] != ' ')
			len_pipe = 0;
		if (len_pipe > 1)
			return (true);
		i++;
	}
	return (false);
}

bool	simple_error(char *command)
{
	if (command[0] == '|' || check_pipe_valid(command))
	{
		ft_putstr("syntax error near unexpected token `", 2);
		ft_putstr("|", 2);
		ft_putstr("'\n", 2);
		return (true);
	}
	return (false);
}
