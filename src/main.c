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

void	insert_data(t_data *data, char *command)
{
	int		i;
	char	**spliting;

	i = 0;
	data->command = command;
	spliting = split_2(command, '|');
	while (spliting[i])
	{
		data->btree = insert_into_btree(data->btree, i, spliting[i]);
		i++;
	}
	free(spliting);
}

void	master(char *command, t_data *data)
{
	int		i;
	t_btree	*aux;

	i = 0;
	insert_data(data, command);
	aux = data->btree;
	if (ft_strlen(aux->content[i]) == 0)
		i++;
	while (aux)
	{
		if (!ft_strncmp(aux->content[i], "exit", ft_strlen(aux->content[i])))
			exit_(data);
		else if (!ft_strncmp(aux->content[i], "pwd", ft_strlen(aux->content[i])))
			pwd(data);
		else if (!ft_strncmp(aux->content[i], "cd", ft_strlen(aux->content[i])))
			cd(data);
		else if (!ft_strncmp(aux->content[i], "echo", ft_strlen(aux->content[i])))
			echo(data);
		else if (!ft_strncmp(aux->content[i], "env", ft_strlen(aux->content[i])))
			env(data);
		else if (!ft_strncmp(aux->content[i], "export", ft_strlen(aux->content[i])))
			export(data);
		else if (!ft_strncmp(aux->content[i], "unset", ft_strlen(aux->content[i])))
			unset(data);
		else
			other_command(data);
		aux = aux->right;
	}
	free_all_data(data);
}

int	main(void)
{
	t_data	data;

	init_data(&data);
	data.path = ft_split(getenv("PATH"), ':');
	data.envp = get_environment();
	master("cd src", &data);
	master("export ", &data);
	master("exit", &data);
	return (0);
}
