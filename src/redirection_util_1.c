/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	first_str(char chr, char *str)
{
	if (str[0] == chr)
		return (true);
	return (false);
}

int	count_chr(char chr, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == chr)
			count++;
		i++;
	}
	return (count);
}

int	get_position_chr(char chr, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == chr)
			return (i);
		i++;
	}
	return (-1);
}

bool	check_valid_redirection(int pos, char *str)
{
	bool	i1;
	bool	i2;
	int		aux_value;

	i1 = true;
	i2 = true;
	aux_value = pos;
	while (str[pos])
	{
		if (str[pos] == '\'' || str[pos] == '"')
			i1 = false;
		pos++;
	}
	pos = aux_value;
	while (str[pos])
	{
		if (str[pos] == '\'' || str[pos] == '"')
			i2 = false;
		pos--;
	}
	if (i1 == false && i2 == false)
		return (false);
	return (true);
}

bool	is_redirection(char *str)
{
	int	gt_count;
	int	lt_count;

	gt_count = count_chr('>', str);
	lt_count = count_chr('<', str);
	if ((gt_count > 0 && gt_count < 3 && lt_count == 0)
		|| (lt_count > 0 && lt_count < 3 && gt_count == 0))
	{
		if (gt_count == 1 && check_valid_redirection(get_position_chr('>', str)
				, str))
			return (true);
		else if (lt_count == 1 && check_valid_redirection(get_position_chr('<',
					str), str))
			return (true);
		else if (gt_count == 2 && str[get_position_chr('>', str) + 1] == '>'
			&& check_valid_redirection(get_position_chr('>', str), str))
			return (true);
		else if (lt_count == 2 && str[get_position_chr('<', str) + 1] == '<'
			&& check_valid_redirection(get_position_chr('<', str), str))
			return (true);
	}
	return (false);
}
