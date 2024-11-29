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

static int	is_directory_valid(const char *path)
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

void	cd(t_data *data)
{
	int		i;
	char	*dir;
	char	*home;

	i = len_matrix(data->btree->content);
	if (i > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		change_environment_variables_question_mark(1, data);
		return ;
	}
	update_oldwpd(data);
	dir = data->btree->content[1];
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
