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
	data->output = dir;
}
