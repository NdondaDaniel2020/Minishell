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
