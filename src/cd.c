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

void	update_pwd_in_cd(t_data *data)
{
	/* add nivel de acesso*/
	int		i;
	int		len;
	char	*cwd;
	char	*pwd;
	char	*oldpwd;

	cwd = ft_calloc(5048, sizeof(char));
	if (!cwd)
		return ;
	i = 0;
	getcwd(cwd, 5048);
	pwd = ft_strjoin("export PWD=", cwd);
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD", 3))
		{
			oldpwd = ft_strjoin("export OLD", data->envp[i]);
			break ;
		}
		i++;
	}
	free(cwd);
	len = len_btree(data->btree);
	// data->automatic_input = true;
	data->btree = insert_into_btree(data->btree, len, pwd);
	export(data);
	data->btree = remove_tree(data->btree, len);
	// data->automatic_input = true;
	data->btree = insert_into_btree(data->btree, len, oldpwd);
	export(data);
	data->btree = remove_tree(data->btree, len);
}

void	cd(t_data *data)
{
	int		i;
	char	*dir;
	char	*home;


	i = 0;
	while (data->btree->content[i])
		i++;
	i--;
	dir = data->btree->content[i];
	if (is_directory_valid(dir))
		chdir(dir);
	else if (condition_home(dir))
	{
		home = getenv("HOME");
		chdir(home);
		data->output = home;
		return ;
	}
	else if (ft_strnstr(dir, "~/", ft_strlen(dir)))
	{
		home = getenv("HOME");
		dir = ft_strjoin(home, &dir[1]);
		chdir(dir);
	}
	update_pwd_in_cd(data);
	data->output = dir;
}
