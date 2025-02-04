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

bool	is_not_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if(!ft_isdigit(str[i]))
		return (true);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (true);
		i++;
	}
	return (false);
}

int	check_error_exit(int ex, t_new_list *aux)
{
	int	len_m;

	len_m = len_matrix(aux->content);
	if (len_m > 1)
	{
		if (is_not_number(aux->content[1]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(aux->content[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (2);
		}
	}
	return (ex);
}

int	numeric_argument_required(char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}
