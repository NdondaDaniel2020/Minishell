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

static bool	check_error_exit(int i, int *ex, t_data *data)
{
	int i2;
	
	i2 = 0;
	while (data->btree->content[i][i2])
	{
		if
		((ft_strlen(data->btree->content[i]) == 1 &&
			!ft_isdigit(data->btree->content[i][i2])) ||
			(ft_strlen(data->btree->content[i]) > 1 && i2 > 0 &&
			!ft_isdigit(data->btree->content[i][i2])) ||
			(ft_strlen(data->btree->content[i]) > 1 && i2 == 0 &&
			(!ft_isdigit(data->btree->content[i][i2]) && 
			data->btree->content[i][i2] != '-')))
		{
			*ex = 2;
			write(2, "exit: ", 6);
			ft_putstr_fd(data->btree->content[i], 2);
			write(2, ": numeric argument required\n", 28);
			return (true);
		}
		i2++;
	}
	return (false);
}

static void free_data(t_data *data)
{
	if (data->path)
		free_matrix(data->path);
	if (data->envp)
		free_matrix(data->envp);
	free_all_data(data);
}

void	exit_(t_data *data)
{
	int	i;
	int ex;

	i = 1;
	ex = 0;
	ft_printf("exit\n");
	while (data->btree->content[i])
	{
		if (i == 1)
		{
			if (check_error_exit(i, &ex, data))
				break ;
			if (ex == 0 && ft_strlen(data->btree->content[i]))
				ex = (unsigned char)ft_atoi(data->btree->content[i]);
		}	
		i++;
	}
	if (len_matrix(data->btree->content) > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		change_environment_variables_question_mark(1, data);
		return ;
	}
	free_data(data);
	exit(ex);
}
