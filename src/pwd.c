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

	i = len_matrix(data->btree->content);
	if (i > 1)
	{
		ft_printf("pwd: too many arguments\n");
		change_environment_variables_question_mark(1, data);
		return ;
	}
	cwd = ft_calloc(5048, sizeof(char));
	if (!cwd)
	{
		change_environment_variables_question_mark(2, data);
		return ;
	}
	if (getcwd(cwd, 5048) == NULL)
	{
		free(cwd);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	change_environment_variables_question_mark(0, data);
}
