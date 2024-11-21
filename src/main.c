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
	spliting = ft_split(command, '|');
	while (spliting[i])
	{
		data->btree = insert_into_btree(data->btree, i, spliting[i]);
		i++;
	}
	free(spliting);
}

void	master(char *command, t_data *data)
{
	t_btree	*aux;

	insert_data(data, command);
	aux = data->btree;
	while (aux)
	{
		if (!ft_strncmp(aux->content[0], "exit", ft_strlen(aux->content[0])))
			exit_(data);
		else if (!ft_strncmp(aux->content[0], "pwd", ft_strlen(aux->content[0])))
			pwd(data);
		else if (!ft_strncmp(aux->content[0], "cd", ft_strlen(aux->content[0])))
			cd(data);
		else if (!ft_strncmp(aux->content[0], "echo", ft_strlen(aux->content[0])))
			echo(data);
		else if (!ft_strncmp(aux->content[0], "env", ft_strlen(aux->content[0])))
			env(data);
		else if (!ft_strncmp(aux->content[0], "export", ft_strlen(aux->content[0])))
			export(data);
		else if (!ft_strncmp(aux->content[0], "unset", ft_strlen(aux->content[0])))
			unset(data);
		else
			other_command(data);
		aux = aux->right;
	}
	free_all_data(data);
}

void	update_pwd(t_data *data)
{
	/* add nivel de acesso*/
	char	*cwd;
	char	*pwd;
	char	*oldpwd;

	cwd = ft_calloc(5048, sizeof(char));
	if (!cwd)
		return ;
	getcwd(cwd, 5048);
	pwd = ft_strjoin("export PWD=", cwd);
	oldpwd = ft_strjoin("export OLDPWD=", cwd);
	free(cwd);
	data->automatic_input = true;
	data->btree = insert_into_btree(data->btree, 0, pwd);
	export(data);
	free_all_data(data);
	data->automatic_input = true;
	data->btree = insert_into_btree(data->btree, 0, oldpwd);
	export(data);
	free_all_data(data);
}

/*
	master("export ___ASD=ASDASD", &data);
	master("export ", &data);
	master("exit", &data);
*/

int	main(void)
{
	t_data	data;
	// char	*input;

	init_data(&data);
	data.path = ft_split(getenv("PATH"), ':');
	data.envp = concat_env(get_env_1(), get_env_2());
	update_pwd(&data);
	master("cd src/", &data);
	// master(" ", &data);
	master("exit", &data);
	// while (1)
	// {
	// 	input = readline("TeamWork> ");
	// 	add_history(input);
	// 	if (ft_strlen(input) != 0)
	// 	{
	// 		master(input, &data);
	// 		free(input);
	// 	}
	// }
	return (0);
}
