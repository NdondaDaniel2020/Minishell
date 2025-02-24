/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
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

void	update_pwd(t_data *data)
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

void	update_oldwpd(t_data *data)
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

bool	add_expanded_variable(t_new_list *aux, t_data *data)
{
	char	*value_env;
	char	**new_content;

	if (ft_strlen(aux->content[1]) > 1)
	{
		value_env = get_env(aux->content[1] + 1, data);
		if (value_env)
			add_in_list(value_env, aux, data);
		else
		{
			new_content = ft_calloc(3, sizeof(char *));
			new_content[0] = ft_strdup("cd");
			new_content[1] = ft_strdup(get_env("HOME", data));
			ft_lstnew_addafter_pos(&data->list, data->list,
				ft_lstnew_new(new_content));
		}
		return (true);
	}
	return (false);
}

bool	check_many_arguments(t_new_list *aux)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (aux->content[i])
	{
		if (ft_strlen(aux->content[i]) == 0)
		{
			i++;
			continue ;
		}
		i++;
		len++;
	}
	if (len > 2 || len == 1)
	{
		if (len == 1)
			ft_putstr_fd("cd: too few arguments\n", 2);
		else
			ft_putstr_fd("cd: too many arguments\n", 2);
		return (true);
	}
	return (false);
}
