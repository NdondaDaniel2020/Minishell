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

	i = 0;
	while (data->btree->content[i])
		i++;
	change_environment_variables_question_mark(0, data);
	if (data->path)
		free_matrix(data->path);
	if (data->envp)
		free_matrix(data->envp);
	free_all_data(data);
	ft_printf("exit\n");
	if (i > 1)
		write(2, "exit: too many arguments\n", 25);
	if (i == 1)	
		exit(0);
}
