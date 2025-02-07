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

static bool	skip_and_sign(const char *str, int *i, int *sign)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	if (!('0' <= str[*i] && str[*i] <= '9'))
		return (false);
	return (true);
}

static long long	to_long(const char *str, int *i, int sign, bool *error)
{
	long long	num;

	num = 0;
	while ('0' <= str[*i] && str[*i] <= '9')
	{
		if ((num > LLONG_MAX / 10)
			|| (num == LLONG_MAX / 10 && (str[*i] - '0') > 8))
		{
			*error = true;
			if (sign == 1)
				return (LLONG_MAX);
			return (LLONG_MIN);
		}
		num = num * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (num);
}

long long	ft_atoll(const char *str, bool *error)
{
	int			i;
	int			sign;
	long long	num;

	i = 0;
	sign = 1;
	*error = false;
	if (!skip_and_sign(str, &i, &sign))
	{
		*error = true;
		return (0);
	}
	num = to_long(str, &i, sign, error);
	if (*error)
		return (0);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		*error = true;
	return (num * sign);
}

static void	free_and_exit(int ex, t_data *data)
{
	free_data(data);
	exit(ex);
}

void	exit_(t_new_list *aux, t_data *data)
{
	int			len;
	long long	exit_code;
	bool		error;

	len = len_matrix(aux->content);
	ft_putstr_fd("exit\n", 1);
	if (len == 1)
		free_and_exit(0, data);
	exit_code = ft_atoll(aux->content[1], &error);
	if (error)
	{
		numeric_argument_required(aux->content[1]);
		free_and_exit(2, data);
	}
	if (exit_code == LLONG_MIN)
		free_and_exit(0, data);
	if (len > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		change_environment_variables_question_mark(1, data);
		return ;
	}
	free_and_exit((unsigned char)exit_code, data);
}
