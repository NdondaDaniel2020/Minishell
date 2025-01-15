/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_error_exit(int i, int *ex, t_new_list *aux)
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

int	numeric_argument_required(char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}
