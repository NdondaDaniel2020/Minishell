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
	if (!ft_isdigit(str[*i]))
		return (false);
	return (true);
}

static long long	ft_util_atoll(int i, int sign, char *str, bool *error)
{
	long long	num;

	num = 0;
	while (ft_isdigit(str[i]))
	{
		if (num > (LLONG_MAX - (str[i] - '0')) / 10)
		{
			*error = true;
			if (sign == 1)
				return (LLONG_MAX);
			return (LLONG_MIN);
		}
		num = num * 10 + (str[i++] - '0');
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		*error = true;
	return (num * sign);
}

long long	ft_atoll(const char *str, bool *error)
{
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	*error = false;
	if (!skip_and_sign(str, &i, &sign))
	{
		*error = true;
		return (0);
	}
	return (ft_util_atoll(i, sign, (char *)str, error));
}

static int	free_and_exit(int ex, t_data *data)
{
	free_data(data);
	exit(ex);
	return (ex);
}

int	exit_(t_new_list *aux, t_data *data)
{
	int			len;
	long long	exit_code;
	bool		error;

	len = len_matrix(aux->content);
	ft_putstr_fd("exit\n", 1);
	if (len == 1)
		free_and_exit(ft_atoi(get_env("?", data)), data);
	exit_code = ft_atoll(aux->content[1], &error);
	if (error)
	{
		if ((int)((aux->content[1][ft_strlen(aux->content[1]) - 1]) - '0')
			== (int)(-1 * (exit_code % 10)))
			free_and_exit(0, data);
		else
		{
			numeric_argument_required(aux->content[1]);
			free_and_exit(2, data);
		}
	}
	if (len > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		return (change_environment_variables_question_mark(1, data));
	}
	return (free_and_exit((unsigned char)exit_code, data));
}
