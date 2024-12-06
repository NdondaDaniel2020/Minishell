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

int	count_chr(char  *command, char chr)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (command[i])
	{
		if (command[i] == chr)
			len++;
		i++;
	}
	return (len);
}

void    master(char *command, t_data *data)
{
    int     i;
    t_btree *aux;

	if (count_chr(command, '\'')  % 2 != 0 || count_chr(command, '"') % 2 != 0)
	{
		ft_putstr("unclosed quotes\n", 2);
		return ;
	}

    insert_data(data, command);
    aux = data->btree;
    while (aux)
    {
        i = 0;
        if (ft_strlen(aux->content[i]) == 0)
            i++;

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
            other_command(aux, data);
        
        aux = aux->right;
    }
    free_all_data(data);
}

int	main(void)
{
	t_data	data;
	// char	*input;

	init_data(&data);
	data.path = ft_split(getenv("PATH"), ':');
	data.envp = get_all_environment();
	master("export A=ls", &data);
	master("$A", &data);
	master("exit", &data);

	// while (1)
	// {
	// 	input = readline("TeamWork> ");
	// 	if (input[0] != '\0')
	// 	{
	// 		add_history(input);
	// 		master(input, &data);
	// 		free(input);
	// 	}
	// }
	return (0);
}
