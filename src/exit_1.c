/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	if (data->path)
		free_matrix(data->path);
	if (data->envp)
		free_matrix(data->envp);
	free_all_data(data);
}

static bool	check_too_many_arguments(t_data *data)
{
	write(2, "exit: too many arguments\n", 25);
	change_environment_variables_question_mark(1, data);
	return (true);
}

static void	free_and_exit(int ex, t_data *data)
{
	free_data(data);
	exit(ex);
}

void	exit_(t_new_list *aux, t_data *data)
{
	int	ex;
	int	len;

	ex = 0;
	ft_printf("exit\n");
	len = len_matrix(aux->content);
	ex = check_error_exit(ex, aux);
	if (ex != 0)
		return ;
	else if (len > 1 && ft_strlen(aux->content[0]) > 19)
		free_and_exit(numeric_argument_required(aux->content[1]), data);
	else if (len == 2 && ft_strlen(aux->content[0]))
		free_and_exit((unsigned char)ft_atoi(aux->content[1]), data);
	else if (len > 2 && check_too_many_arguments(data))
		return ;
	free_and_exit(ex, data);
}
