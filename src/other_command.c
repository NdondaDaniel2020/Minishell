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

void	adjustment_001(t_new_list *aux)
{
	t_new_list *new_aux;

	new_aux = aux;
	while (new_aux)
	{
		int i = 0;
		while (new_aux->content[i])
		{
			if (ft_strlen(new_aux->content[i]) == 2
			&& new_aux->content[i][0] == 1 && new_aux->content[i][1] == 1)
			{
				new_aux->content[i][0] = 0;
				new_aux->content[i][1] = 0;
			}
			i++;
		}
		new_aux = new_aux->next;
	}
}

static char	*read_all_path(int i, t_new_list *aux, t_data *data,
	DIR *open_dir)
{
	char			*dir_path;
	struct dirent	*entry;

	entry = readdir(open_dir);
	while (entry != NULL)
	{
		if (!ft_strncmp(entry->d_name, aux->content[0],
				ft_strlen(entry->d_name)) && ft_strlen(entry->d_name)
			== ft_strlen(aux->content[0]))
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

char	*get_valid_path(t_new_list *aux, t_data *data)
{
	int		i;
	char	*dir_path;
	DIR		*open_dir;

	i = 0;
	if (data->path == NULL)
		return (NULL);
	adjustment_001(aux);
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

static int	other_case_execution( t_new_list *aux, t_data *data)
{
	ft_putstr_fd(aux->content[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (change_environment_variables_question_mark(127, data));
}

int	other_command(int i, t_new_list *aux, t_data *data)
{
	int			pid;
	int			ret;
	t_index_str	*path;

	ret = 0;
	path = get_absolute_path(i, aux, data);
	if (path->index == -1)
		return (free(path), 1);
	if (path->index == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path->str, aux->content, data->envp) == -1)
				exit(EXIT_FAILURE);
			exit(0);
		}
		wait(&ret);
		free(path->str);
		free(path);
		return (change_environment_variables_question_mark(ret, data));
	}
	else
		ret = other_case_execution(aux, data);
	return (free(path), change_environment_variables_question_mark(ret, data));
}
