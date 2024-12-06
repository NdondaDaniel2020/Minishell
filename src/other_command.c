/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_comand.c                                     :+:      :+:    :+:   */
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

char	*get_valid_path(t_data *data)
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












void	other_command(t_btree *aux, t_data *data)
{
	int		pid;
	char	*path;

	if (ft_strnstr(aux->content[0], "/",
			ft_strlen(aux->content[0])))
		path = ft_strdup(aux->content[0]);
	else
		path = get_valid_path(data);
	if (path)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(path, aux->content, data->envp);
		}
		else
		{
			wait(NULL);
		}
		free(path);
	}
	else
	{
		// criar expancao
		if (ft_strchr(aux->content[0], '$'))
		{
			int		i;
			char	*str;

			i = 0;
			while (data->envp[i])
			{
				if (!ft_strncmp((aux->content[0] + 1), data->envp[i], ft_strlen(aux->content[0] + 1)))
				{
					if (is_directory_valid(data->envp[i] + ft_strlen(aux->content[0])))
						ft_printf("%s: Is a directory\n", data->envp[i] + ft_strlen(aux->content[0]));
					else
					{
						str = ft_strdup(data->envp[i] + ft_strlen(aux->content[0]));
						data->btree = insert_into_btree(data->btree, len_btree(data->btree), str);
						data->btree = data->btree->right;
					}
					break ;
				}
				i++;
			}
		}
		else
			ft_printf("%s: command not found\n", data->btree->content[0]);
	}
}
