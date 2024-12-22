/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	adjust_value_error(int i, char *str_pos)
{
	while (str_pos[i] == ' ')
		i++;
	return (i);
}

static int	get_value_erro(char *str, char *str_pos)
{
	if (ft_strncmp(str, list_error()[0], ft_strlen(list_error()[0])) == 0)
		return (1);
	if ((ft_strncmp(str, list_error()[1], ft_strlen(list_error()[1])) == 0)
		|| (ft_strncmp(str, list_error()[2], ft_strlen(list_error()[2])) == 0)
		|| (ft_strncmp(str, list_error()[3], ft_strlen(list_error()[3])) == 0)
		|| (ft_strncmp(str, list_error()[4], ft_strlen(list_error()[4])) == 0)
		|| (ft_strncmp(str, list_error()[5], ft_strlen(list_error()[5])) == 0)
		|| (ft_strncmp(str, list_error()[6], ft_strlen(list_error()[6])) == 0))
		return (2);
	if ((ft_strncmp(str, list_error()[7], ft_strlen(list_error()[7])) == 0)
		|| (ft_strncmp(str, list_error()[8], ft_strlen(list_error()[8])) == 0)
		|| (ft_strncmp(str, list_error()[9], ft_strlen(list_error()[9])) == 0))
		return (adjust_value_error(3, str_pos));
	if ((ft_strncmp(str, list_error()[10], ft_strlen(list_error()[10])) == 0) ||
		(ft_strncmp(str, list_error()[11], ft_strlen(list_error()[11])) == 0))
		return (adjust_value_error(2, str_pos));
	return (0);
}

static bool	check_redirection_error(int i1, int i2, t_var_red *red, char *str)
{
	int	pos;

	if (ft_strncmp(red->extract_matrix[i1]->string, red->list_error[i2],
		ft_strlen(red->list_error[i2])) == 0)
	{
		pos = ft_strnpos(str, red->extract_matrix[i1]->string, ft_strlen(str));
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(str[pos + get_value_erro(red->list_error[i2],
			 str + pos)], 2);
		ft_putstr_fd("'\n", 2);
		free_extract_matrix(red->extract_matrix);
		return (true);
	}
	return (false);
}

static bool	redirection_is_string(int i1, t_var_red	*red, char *str)
{
	int	pos;

	pos = ft_strnpos(str, red->extract_matrix[i1]->string, ft_strlen(str));
	if (check_valid_redirection(pos, str) == false)
		return (true);
	return (false);
}

int	is_redirection(char *str)
{
	int			i1;
	int			i2;
	t_var_red	red;

	if (str == NULL || (count_chr('<', str) == 0 && count_chr('>', str) == 0))
		return (0);
	i1 = 0;
	init_var_redirection(&red);
	red.list_error = list_error();
	red.extract_matrix = extract_all_redirection_characters(str);
	while (red.extract_matrix[i1])
	{
		i2 = 0;
		while (red.list_error[i2])
		{
			if (redirection_is_string(i1, &red, str))
				return (0);
			if (check_redirection_error(i1, i2, &red, str))
				return (2);
			i2++;
		}
		i1++;
	}
	free_extract_matrix(red.extract_matrix);
	return (1);
}