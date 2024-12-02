/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_(t_data *data)
{
	int	i;

	change_environment_variables_question_mark(0, data);
	i = 0;
	ft_printf("exit\n");
	while (data->btree->content[i])
	{
		if (i > 0 && ft_strlen(data->btree->content[i]) > 0)
		{
			write(2, "exit: too many arguments\n", 25);
			change_environment_variables_question_mark(1, data);
		}
		i++;
	}
	if (data->path)
		free_matrix(data->path);
	if (data->envp)
		free_matrix(data->envp);
	free_all_data(data);
	exit(0);
}
