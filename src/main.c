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
	data->path = ft_split(getenv("PATH"), ':');
	data->envp = concat_env(get_env_1(), get_env_2());
}

char	*get_valid_path(t_data *data)
{
	
	int				i;
	DIR				*open_dir;
	char			*dir_path;
	struct dirent	*entry;

	i = 0;
	while (data->path[i])
	{
		open_dir = opendir(data->path[i]);
		if (open_dir)
		{
			entry = readdir(open_dir);
			while (entry != NULL)
			{
				if (!ft_strncmp(entry->d_name, data->btree->content[0],
					ft_strlen(entry->d_name)) && ft_strlen(entry->d_name)
					== ft_strlen(data->btree->content[0]))
				{
					dir_path = ft_charjoin(data->path[i], '/');
					dir_path = ft_strjoin_free(dir_path, entry->d_name);
					closedir(open_dir);
					return (dir_path);
				}
				entry = readdir(open_dir);
			}
		}
		closedir(open_dir);
		i++;
	}
	return (NULL);
}

void	other_command(t_data *data)
{
	int		pid;
	char	*path;
	

	if (ft_strnstr(data->btree->content[0], "/", ft_strlen(data->btree->content[0])))
		path = ft_strdup(data->btree->content[0]);
	else
		path = get_valid_path(data);
	if (path)
	{
		pid = fork();
		if (pid == 0)
		{
			// ft_printf("%s -> %s\n", path, data->btree->content[0]);
			execve(path, data->btree->content, data->envp);
		}
		else
		{
			wait(NULL);
			// ft_printf("[pai %i] -> %s\n", pid, path);
		}
		free(path);
	}
	else
		ft_printf("COMANDO INAVALIDO\n"); /* meter o verdadeiro erro */
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
		else if (!ft_strncmp(aux->content[0], "env", ft_strlen(aux->content[0])))
			env(&data);
		else
			other_command(&data);
		aux = aux->right;
	}
	free_all_data(&data);
}

int	main(void)
{
	char	*input;

	// master("pwd");
	// master("clear");
	while (1)
	{
		input = readline("TeamWork> ");
		add_history(input);
		if (ft_strlen(input) != 0)
		{
			master(input);
			free(input);
		}
	}
	return (0);
}
