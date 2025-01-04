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

static char	*read_all_path(int i, t_new_list *aux, t_data *data, DIR *open_dir)
{
	char			*dir_path;
	struct dirent	*entry;

	entry = readdir(open_dir);
	while (entry != NULL)
	{
		if (!ft_strncmp(entry->d_name, aux->content[0],
				ft_strlen(entry->d_name)) && ft_strlen(entry->d_name)
			== ft_strlen(data->list->content[0]))
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

static char	*get_valid_path(t_new_list *aux, t_data *data)
{
	int				i;
	char			*dir_path;
	DIR				*open_dir;

	i = 0;
	if (data->path == NULL)
		return (NULL);
	while (data->path[i])
	{
		open_dir = opendir(data->path[i]);
		if (open_dir)
		{
			dir_path = read_all_path(i, aux, data, open_dir);
			if (dir_path)
				return (dir_path);
		}
		closedir(open_dir);
		i++;
	}
	return (NULL);
}

static void	error_command_not_found(t_new_list *aux)
{
	ft_putstr_fd(aux->content[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

char	*get_absolute_path(int i, t_new_list *aux, t_data *data)
{
	if (ft_strnstr(aux->content[i], "/", ft_strlen(aux->content[i])))
	{
		if (aux->content[i][ft_strlen(aux->content[i]) - 1] == '/')
		{
			if (is_directory_valid(aux->content[i]))
			{
				ft_putstr_fd(aux->content[i], 2);
				ft_putstr_fd(": Is a directory\n", 2);
			}
			else
			{
				ft_putstr_fd(aux->content[i], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
			}
			return (NULL);
		}
		else
			return (ft_strdup(aux->content[i]));
	}
	else
		return (get_valid_path(aux, data));
}

void	other_command(int i, t_new_list *aux, t_data *data)
{
	int		pid;
	int		status;
	char	*path;

	path = get_absolute_path(i, aux, data);
	if (path == NULL)
		return ;
	if (path)
	{
		pid = fork();

		if (pid == 0)
		{
			if (execve(path, aux->content, data->envp) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			// if (status != 0)
			// 	// erro
			// else
			// 	// ls
		}
		free(path);
	}
	else
	{
		if (ft_strchr(aux->content[i], '$'))
			check_environment_variable_expansion(aux, data);
		else
			error_command_not_found(aux);
	}
}
