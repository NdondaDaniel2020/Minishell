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
	spliting = ft_split(command, '|');
	while (spliting[i])
	{
		data->btree = insert_into_btree(data->btree, i, spliting[i]);
		i++;
	}
	free(spliting);
}

void	master(char *command)
{
	t_btree	*aux;
	t_data	data;

	init_data(&data);
	data.command = command;
	insert_data(&data, command);
	aux = data.btree;
	while (aux)
	{
		if (!ft_strncmp(aux->content[0], "exit", ft_strlen(aux->content[0])))
			exit_(&data);
		else if (!ft_strncmp(aux->content[0], "pwd", ft_strlen(aux->content[0])))
			pwd(&data);
		else if (!ft_strncmp(aux->content[0], "cd", ft_strlen(aux->content[0])))
			cd(&data);
		else if (!ft_strncmp(aux->content[0], "echo", ft_strlen(aux->content[0])))
			echo(&data);
		// else
			// pegar path: e concatenar com cada parte do bin para ver se funciona
			// se nao funcionar mostrar sms de erro
		aux = aux->right;
	}
	// free_all_data(&data);
}

int	main(void)
{
	// char	*input;
	master("echo -n TEST TST AXD VASDF $HOME $HOME $HOME $HOME $HOME $HOME $HOME $HOME");
	// while (1)
	// {
	// 	input = readline("TeamWork> ");
	// 	add_history(input);
	// 	if (ft_strlen(input) != 0)
	// 	{
	// 		master(input);
	// 		free(input);
	// 	}
	// }
	return (0);
}
