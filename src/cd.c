/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory_valid(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

static int	condition_home(char *dir)
{
	if ((ft_strnstr(dir, "~", ft_strlen(dir))
			&& !ft_strnstr(dir, "~/", ft_strlen(dir)))
		|| ft_strnstr(dir, "cd", ft_strlen(dir))
		|| ft_strnstr(dir, " ", ft_strlen(dir)))
		return (1);
	return (0);
}

static void	update_pwd(t_data *data)
{
	char	*cwd;
	char	*pwd;

	cwd = ft_calloc(5048, sizeof(char));
	if (!cwd)
		return ;
	getcwd(cwd, 5048);
	pwd = ft_strjoin("PWD=", cwd);
	add_environment_variable(pwd, data);
	free(pwd);
	free(cwd);
}

static void	update_oldwpd(t_data *data)
{
	char	*cwd;
	char	*oldpwd;

	cwd = ft_calloc(5048, sizeof(char));
	if (!cwd)
		return ;
	getcwd(cwd, 5048);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	add_environment_variable(oldpwd, data);
	free(oldpwd);
	free(cwd);
}

static bool	add_expanded_variable(t_new_list *aux, t_data *data)
{
	int		i;
	char	*value_env;
	char	**split_cmd;
	char	**new_content;

	i = 0;
	value_env = get_env(aux->content[1] + 1, data);
	if (value_env)
	{
		value_env = ft_strtrim(value_env, "\"'");
		split_cmd = split_2(value_env, ' ');
		new_content = ft_calloc(len_matrix(split_cmd) + 2, sizeof(char *));
		new_content[i] = ft_strdup(aux->content[0]);
		while (split_cmd[i])
		{
			new_content[i + 1] = split_cmd[i];
			i++;
		}
		new_content[i + 1] = NULL;
		ft_lstnew_addback(&data->list, ft_lstnew_new(new_content));
		free(split_cmd);
		free(value_env);
	}
	else
	{
		new_content = ft_calloc(3, sizeof(char *));
		new_content[0] = ft_strdup("cd");
		new_content[1] = ft_strdup(get_env("HOME", data));
		ft_lstnew_addback(&data->list, ft_lstnew_new(new_content));
	}
	return (true);
}


void	cd(t_new_list *aux, t_data *data)
{
	int		i;
	char	*dir;
	char	*home;

	if (ft_strchr(aux->content[1], '$'))
		if (add_expanded_variable(aux, data))
			return ;
	i = len_matrix(aux->content);
	if (i > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		change_environment_variables_question_mark(1, data);
		return ;
	}

	update_oldwpd(data);
	dir = aux->content[1];
	if (is_directory_valid(dir))
		chdir(dir);
	else if (condition_home(dir))
	{
		home = getenv("HOME");
		chdir(home);
	}
	else if (ft_strnstr(dir, "~/", ft_strlen(dir)))
	{
		home = getenv("HOME");
		dir = ft_strjoin(home, &dir[1]);
		chdir(dir);
		free(dir);
	}
	else
	{
		change_environment_variables_question_mark(1, data);
		write(2, "cd: ", 4);
		ft_putstr_fd(dir, 2);
		write(2, ": No such file or directory\n", 28);
		return ;
	}
	update_pwd(data);
	change_environment_variables_question_mark(0, data);
}
