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

static bool	check_error_exit(int i, int *ex, t_new_list *aux)
{
	int	i2;

	i2 = 0;
	while (aux->content[i][i2])
	{
		if ((ft_strlen(aux->content[i]) == 1
				&& !ft_isdigit(aux->content[i][i2]))
			|| (ft_strlen(aux->content[i]) > 1 && i2 > 0
			&& !ft_isdigit(aux->content[i][i2]))
			|| (ft_strlen(aux->content[i]) > 1 && i2 == 0
			&& (!ft_isdigit(aux->content[i][i2]) &&
			aux->content[i][i2] != '-')))
		{
			*ex = 2;
			write(2, "exit: ", 6);
			ft_putstr_fd(aux->content[i], 2);
			write(2, ": numeric argument required\n", 28);
			return (true);
		}
		i2++;
	}
	return (false);
}

static void	free_data(t_data *data)
{
	if (data->path)
		free_matrix(data->path);
	if (data->envp)
		free_matrix(data->envp);
	free_all_data(data);
}

static bool	check_too_many_arguments(t_new_list *aux, t_data *data)
{
	int	i;
	int	len;

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
	if (len > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		change_environment_variables_question_mark(1, data);
		return (true);
	}
	return (false);
}

static void	init_var(int *i, int *ex, int *len)
{
	*i = 0;
	*ex = 0;
	*len = 0;
	ft_printf("exit\n");
}

static void	free_and_exit(int ex, t_data *data)
{
	free_data(data);
	exit(ex);
}

void	exit_(t_new_list *aux, t_data *data)
{
	int	i;
	int	ex;
	int	len;

	init_var(&i, &ex, &len);
	while (aux->content[i])
	{
		if (ft_strlen(aux->content[i]) == 0)
		{
			i++;
			continue ;
		}
		if (len == 1)
		{
			if (check_error_exit(i, &ex, aux))
				break ;
			if (ex == 0 && ft_strlen(aux->content[i]))
				ex = (unsigned char)ft_atoi(aux->content[i]);
		}
		i++;
		len++;
	}
	if (check_too_many_arguments(aux, data))
		return ;
	free_and_exit(ex, data);
}
