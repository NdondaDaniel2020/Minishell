/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
    char cwd[5048];

    getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}

int is_directory_valid(const char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) != 0)
        return 0;
    return S_ISDIR(path_stat.st_mode);
}

void cd(char *dir)
{
	char	*home;

    if (is_directory_valid(dir))
		chdir(dir);
	else if ((ft_strnstr(dir, "~", ft_strlen(dir)) &&
			!ft_strnstr(dir, "~/", ft_strlen(dir))) ||
			ft_strnstr(dir, "cd", ft_strlen(dir)) ||
			ft_strnstr(dir, " ", ft_strlen(dir)))
	{
		home = getenv("HOME");
		chdir(home);
	}
	else  if (ft_strnstr(dir, "~/", ft_strlen(dir)))
	{
		home = getenv("HOME");
		dir = ft_strjoin(home, &dir[1]);
		chdir(dir);
	}
}

static void	execute_command(char *command)
{
	int		i;
	char	**split_cmd;

	i = 0;
	split_cmd = ft_split(command, ' ');
	if (!ft_strncmp(split_cmd[0], "echo", ft_strlen(split_cmd[0])))
		printf("ECHO\n");
	else if (!ft_strncmp(split_cmd[0], "pwd", ft_strlen(split_cmd[0])))
		pwd();
	else if (!ft_strncmp(split_cmd[0], "cd", ft_strlen(split_cmd[0])))
	{
		i = 0;
		while (split_cmd[i])
			i++;
		cd(split_cmd[i - 1]);
	}
	// free split
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("TeamWork> ");
		add_history(input);
		execute_command(input);
		free(input);
	}
	return (0);
}
