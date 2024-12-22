/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_6.c                               :+:      :+:    :+:   */
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

int	ft_strnpos(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	l_lit;

	i = 0;
	l_lit = ft_strlen(little);
	if (len == 0 && !little)
		return (0);
	if (big == little || l_lit == 0)
		return (0);
	while (*big && i < len)
	{
		c = 0;
		if (*big == little[0])
		{
			while (little[c] == big[c] && little[c] && big[c] && i + c < len)
				c++;
		}
		if (c == l_lit)
			return (i);
		++big;
		i++;
	}
	return (0);
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
