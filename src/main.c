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


void	other_command(t_data *data)
{
	int		i;
	int		pid;
	char	*path;

	//////////////////////////////////////////////////////////////////////////////////
	
	i = 0;
	if (ft_strlen(data->btree->content[i]) == 0)
		i++;
	
	//////////////////////////////////////////////////////////////////////////////////
	
	if (ft_strnstr(data->btree->content[i], "/", ft_strlen(data->btree->content[i])))
		path = ft_strdup(data->btree->content[i]);
	else
		path = get_valid_path(data);
	
	//////////////////////////////////////////////////////////////////////////////////
	
	ft_printf("%s\n", path);

	if (path)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(path, data->btree->content, data->envp);
		}
		else
		{
			wait(NULL);
		}
		free(path);
	}
	else
	{
		change_environment_variables_question_mark(127, data);
		write(2, "command not found: ", 18);
		ft_putstr_fd(data->btree->content[i], 2);
		return ;
	}
	change_environment_variables_question_mark(0, data);

	//////////////////////////////////////////////////////////////////////////////////
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

void	master(char *command, t_data *data)
{
	int		i;
	int		pid;
	t_data	*cpy_data;

	insert_data(data, command);
	cpy_data = data;

	while (data->btree)
	{
		
		i = 0;
		if (ft_strlen(data->btree->content[i]) == 0)
			i++;

		pid = fork();
		if (id == 0)
		{
			/*
			if (data->btree->left)
			{
				dup2(data->write_on_the_pipe, STDOUT_FILENO);
				close(data->write_on_the_pipe);
			}
			if (data->btree->right)
			{
				dup2(data->read_in_the_pipe, STDIN_FILENO);
				close(data->read_in_the_pipe);
			}
			*/
			if (!ft_strncmp(data->btree->content[i], "exit", ft_strlen(data->btree->content[i])))
				exit_(data);
			else if (!ft_strncmp(data->btree->content[i], "pwd", ft_strlen(data->btree->content[i])))
				pwd(data);
			else if (!ft_strncmp(data->btree->content[i], "cd", ft_strlen(data->btree->content[i])))
				cd(data);
			else if (!ft_strncmp(data->btree->content[i], "echo", ft_strlen(data->btree->content[i])))
				echo(data);
			else if (!ft_strncmp(data->btree->content[i], "env", ft_strlen(data->btree->content[i])))
				env(data);
			else if (!ft_strncmp(data->btree->content[i], "export", ft_strlen(data->btree->content[i])))
				export(data);
			else if (!ft_strncmp(data->btree->content[i], "unset", ft_strlen(data->btree->content[i])))
				unset(data);
			else
				other_command(data);

			exit();
		}
		else
		{
			wait(NULL);
			data->btree = data->btree->right;
		}
	}
	
	free_all_data(cpy_data);
}

int	main(void)
{
	t_data	data;
	// char	*input;

	init_data(&data);
	data.path = ft_split(getenv("PATH"), ':');
	data.envp = get_all_environment();
	master("pwd argumento", &data);
	master("cd /caminho1 /caminho2", &data);
	master("echo -z 'texto'", &data);
	master("export 123VALOR=teste", &data);
	master("unset -z VAR", &data);
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
