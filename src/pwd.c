/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	error_pwd(t_new_list *aux, t_data *data)
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
		if (len > 0 && ft_strlen(aux->content[i]) > 0)
		{
			write(2, "pwd: too many arguments\n", 24);
			change_environment_variables_question_mark(1, data);
			return (true);
		}
		i++;
		len++;
	}
	return (false);
}

void	pwd(t_new_list *aux, t_data *data)
{
	char	*cwd;

	if (error_pwd(aux, data))
		return ;
	cwd = ft_calloc(5048, sizeof(char));
	if (!cwd)
	{
		change_environment_variables_question_mark(2, data);
		return ;
	}
	getcwd(cwd, 5048);
	ft_printf("%s\n", cwd);
	free(cwd);
	change_environment_variables_question_mark(0, data);
}
