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
	int		pid;
	char	*path;

	if (ft_strnstr(data->btree->content[0], "/",
			ft_strlen(data->btree->content[0])))
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
		ft_printf("command not found: %s\n", data->btree->content[0]); /* meter o verdadeiro erro */
}
