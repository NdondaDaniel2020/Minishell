/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_data *data)
{
    char *cwd;

	cwd = ft_calloc(5048, sizeof(char));
    if (!cwd)
	    data->output = NULL;
    if (getcwd(cwd, 5048) == NULL)
	{
        free(cwd);
		data->output = NULL;
    }
	ft_printf("%s\n", cwd);
    data->output = cwd;
}

static int	is_directory_valid(const char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) != 0)
        return (0);
    return S_ISDIR(path_stat.st_mode);
}

void	cd(t_data *data)
{
	int		i;
	char	*dir;
	char	*home;

	i = 0;
	while (data->split_cmd[i])
		i++;
	dir = data->split_cmd[i - 1];
    if (is_directory_valid(dir))
		chdir(dir);
	else if ((ft_strnstr(dir, "~", ft_strlen(dir)) && !ft_strnstr(dir,
			"~/", ft_strlen(dir))) || ft_strnstr(dir, "cd",
			ft_strlen(dir)) || ft_strnstr(dir, " ", ft_strlen(dir)))
	{
		home = getenv("HOME");
		chdir(home);
		data->output = home;
	}
	else  if (ft_strnstr(dir, "~/", ft_strlen(dir)))
	{
		home = getenv("HOME");
		dir = ft_strjoin(home, &dir[1]);
		chdir(dir);
	}
	data->output = dir;
}

void	exit_(t_data *data)
{
	// if (data->output)
	// 	free(data->output);
	// if (data->put_amb)
	// 	free(data->put_amb);
	// free_matrix(data->split_cmd);
	(void)data;
	exit(0);
}