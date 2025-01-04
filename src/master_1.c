/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_data(t_data *data, char *command)
{
	int		i;
	char	**spliting;

	i = 0;
	data->command = command;
	spliting = split_2(command, '|');
	while (spliting[i])
	{
		ft_lstnew_addfront(&data->list,
			ft_lstnew_new(split_2(spliting[i], ' ')));
		free(spliting[i]);
		i++;
	}
	free(spliting);
}

void	execute_command(int i, t_new_list *aux, t_data *data)
{
	if (!ft_strncmp(aux->content[i], "exit", ft_strlen(aux->content[i])))
		exit_(aux, data);
	else if (!ft_strncmp(aux->content[i], "pwd", ft_strlen (aux->content[i])))
		pwd(aux, data);
	else if (!ft_strncmp(aux->content[i], "cd", ft_strlen(aux->content[i])))
		cd(aux, data);
	else if (!ft_strncmp(aux->content[i], "echo", ft_strlen(aux->content[i])))
		echo(aux, data);
	else if (!ft_strncmp(aux->content[i], "env", ft_strlen(aux->content[i])))
		env(aux, data);
	else if (!ft_strncmp(aux->content[i], "export", ft_strlen(aux->content[i])))
		export(aux, data);
	else if (!ft_strncmp(aux->content[i], "unset", ft_strlen(aux->content[i])))
		unset(data);
	else
		other_command(i, aux, data);
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
