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

static void	other_case_execution(int i, t_new_list *aux, t_data *data)
{
	if (ft_strchr(aux->content[i], '$'))
	{	
		check_environment_variable_expansion(aux, data);
		change_environment_variables_question_mark(0, data);
	}
	else
	{
		ft_putstr_fd(aux->content[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		change_environment_variables_question_mark(127, data);
	}
}

char	*get_absolute_path(int i, t_new_list *aux, t_data *data)
{
	if (ft_strnstr(aux->content[i], "/", ft_strlen(aux->content[i])))
	{
		if (aux->content[i][ft_strlen(aux->content[i]) - 1] == '/'
			|| is_other_file(aux->content[i]))
		{
			if (is_directory_valid(aux->content[i]))
			{
				ft_putstr_fd(aux->content[i], 2);
				ft_putstr_fd(": Is a directory\n", 2);
				change_environment_variables_question_mark(126, data);
			}
			else
			{
				ft_putstr_fd(aux->content[i], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				change_environment_variables_question_mark(127, data);
			}
			return (NULL);
		}
		else
			return (ft_strdup(aux->content[i]));
	}
	else
		return (get_valid_path(aux, data));
}

int	other_command(int i, t_new_list *aux, t_data *data)
{
	int		pid;
	int		status;
	char	*path;

	path = get_absolute_path(i, aux, data);
	if (path == NULL)
		return (1);
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
			free(path);
			wait(&status);
			return (change_environment_variables_question_mark(0, data));
		}
	}
	else
		other_case_execution(i, aux, data);
	return (change_environment_variables_question_mark(1, data));
}
