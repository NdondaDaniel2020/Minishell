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


static char	*read_all_path(int i, t_data *data, DIR *open_dir)
{
	char			*dir_path;
	struct dirent	*entry;

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
	return (NULL);
}

static char	*get_valid_path(t_data *data)
{
	int				i;
	char			*dir_path;
	DIR				*open_dir;

	i = 0;
	while (data->path[i])
	{
		open_dir = opendir(data->path[i]);
		if (open_dir)
		{
			dir_path = read_all_path(i, data, open_dir);
			if (dir_path)
				return (dir_path);
		}
		closedir(open_dir);
		i++;
	}
	return (NULL);
}




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

int	list_builtins(char *command)
{
	if (ft_strncmp(command, "echo", 4) == 0 && ft_strlen(command) == 4)
		return (1);
	else if (ft_strncmp(command, "cd", 2) == 0 && ft_strlen(command) == 2)
		return (1);
	else if (ft_strncmp(command, "pwd", 3) == 0 && ft_strlen(command) == 3)
		return (1);
	else if (ft_strncmp(command, "export", 6) == 0 && ft_strlen(command) == 6)
		return (1);
	else if (ft_strncmp(command, "unset", 5) == 0 && ft_strlen(command) == 5)
		return (1);
	else if (ft_strncmp(command, "env", 3) == 0 && ft_strlen(command) == 3)
		return (1);
	else if (ft_strncmp(command, "exit", 4) == 0 && ft_strlen(command) == 4)
		return (1);
	return (0);
}





void	master(char *command, t_data *data)
{
	int		i;
	int		pid;
	char	*path;
	t_btree	*aux;

	insert_data(data, command);
	aux = data->btree;
	path = NULL;
	while (aux)
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		i = 0;
		if (ft_strlen(aux->content[i]) == 0)
			i++;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if (ft_strnstr(aux->content[i], "/", ft_strlen(aux->content[i])) ||
			list_builtins(aux->content[i]))
			path = ft_strdup(aux->content[i]);
		else
			path = get_valid_path(data);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		pid = fork();
		if (pid == 0)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (path == NULL)
			{
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				change_environment_variables_question_mark(127, data);
				write(2, "command not found: ", 19);
				ft_putstr_fd(aux->content[i], 2);
				write(2, "\n", 1);
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if (data->path)
					free_matrix(data->path);
				if (data->envp)
					free_matrix(data->envp);
				free_all_data(data);
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				exit(127);
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
			else if (!ft_strncmp(aux->content[i], "exit", ft_strlen(aux->content[i])))
			{
				free(path);
				exit_(data);
			}
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
				execve(path, aux->content, data->envp);

			change_environment_variables_question_mark(0, data);

			if (data->path)
				free_matrix(data->path);
			if (data->envp)
				free_matrix(data->envp);
			free_all_data(data);

			free(path);			
			exit(0);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		else
		{
			wait(NULL);
			free(path);
			aux = aux->right;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!ft_strncmp(data->btree->content[i], "exit", ft_strlen(data->btree->content[i])))
	{
		if (data->path)
		{
			free_matrix(data->path);
			data->path = NULL;
		}
		if (data->envp)
		{
			free_matrix(data->envp);
			data->envp = NULL;
		}
		free_all_data(data);
		exit(0);
	}
	free_all_data(data);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}





int	main(void)
{
	t_data	data;
	char	*input;

	init_data(&data);
	data.path = ft_split(getenv("PATH"), ':');
	data.envp = get_all_environment();

	while (1)
	{
		input = readline("TeamWork> ");
		if (input[0] != '\0')
		{
			add_history(input);
			master(input, &data);
			free(input);
		}
	}
	return (0);
}

