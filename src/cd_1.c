/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	condition_home(char *dir)
{
	if ((ft_strnstr(dir, "~", ft_strlen(dir))
			&& !ft_strnstr(dir, "~/", ft_strlen(dir)))
		|| ft_strnstr(dir, "cd", ft_strlen(dir))
		|| ft_strnstr(dir, " ", ft_strlen(dir)))
		return (1);
	return (0);
}

void	add_in_list(char *value_env, t_new_list *aux, t_data *data)
{
	int		i;
	char	**new_content;
	char	**split_cmd;

	i = 0;
	value_env = ft_strtrim(value_env, "\"'");
	split_cmd = split_2(value_env, ' ');
	new_content = ft_calloc(len_matrix(split_cmd) + 2, sizeof(char *));
	new_content[i] = ft_strdup(aux->content[0]);
	while (split_cmd[i])
	{
		new_content[i + 1] = split_cmd[i];
		i++;
	}
	ft_lstnew_addafter_pos(&data->list, data->list, ft_lstnew_new(new_content));
	free(split_cmd);
	free(value_env);
}

static void	error_file_or_directory(char *dir)
{
	write(2, "cd: ", 4);
	ft_putstr_fd(dir, 2);
	write(2, ": No such file or directory\n", 28);
}

static void	change_dir(char *dir, t_data *data)
{
	char	*home;

	home = get_env("HOME", data);
	dir = ft_strjoin(home, dir + 1);
	chdir(dir);
	free(dir);
}

int	cd(t_new_list *aux, t_data *data)
{
	char	*dir;
	char	*home;

	if (ft_strchr(aux->content[1], '$') && add_expanded_variable(aux, data))
		return (change_environment_variables_question_mark(0, data));
	if (check_many_arguments(aux))
		return (change_environment_variables_question_mark(1, data));
	update_oldwpd(data);
	dir = aux->content[get_last_position(aux)];
	if (is_directory_valid(dir))
		chdir(dir);
	else if (condition_home(dir))
	{
		home = get_env("HOME", data);
		chdir(home);
	}
	else if (ft_strnstr(dir, "~/", ft_strlen(dir)))
		change_dir(dir, data);
	else
	{
		error_file_or_directory(dir);
		return (change_environment_variables_question_mark(1, data));
	}
	update_pwd(data);
	return (change_environment_variables_question_mark(0, data));
}
