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

void	pwd(t_data *data)
{
	int		i;
	char	*cwd;

	i = 0;
	while (data->list->content[i])
	{
		if (i > 0 && ft_strlen(data->list->content[i]) > 0)
		{
			write(2, "pwd: too many arguments\n", 24);
			change_environment_variables_question_mark(1, data);
			return ;
		}
		i++;
	}
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
