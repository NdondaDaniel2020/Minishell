/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	traverse_n(int *i, t_data *data)
{
	while (data->btree->content[*i] && ft_strnstr(data->btree->content[*i],
			"-n", ft_strlen(data->btree->content[*i])))
		(*i)++;
}

// analize as condition tem falhas
static bool	condition_traverse_the_array(int i, int i1, int i2, t_data *data)  /
{
	if (i == 1)
		if (data->btree->content[i1][i2] != '$' &&
			data->btree->content[i1][i2] != '"' &&
			data->btree->content[i1][i2] != '\'')
			return (true);
	if (i == 2)
		if ((data->btree->content[i1][i2] == '\"' &&
		 data->btree->content[i1][i2 + 1] == '$' &&
		 ft_memchr(data->btree->content[i1], '\'', i2)))
			return (true);
	if (i == 3)
		if (data->btree->content[i1][i2] == '$' ||
			(data->btree->content[i1][i2] == '\'' &&
			data->btree->content[i1][i2 + 1] == '$'))
			return (true);
	return (false);
}

static void	put_char_and_join(int i1, int i2, t_data *data)
{
	ft_putchar_fd(data->btree->content[i1][i2], 1);
	data->space = true;
}

int	traverse_the_array(int i1, int i2, t_valid	*valid, t_data *data)
{
	if (condition_traverse_the_array(1, i1, i2, data))
	{
		put_char_and_join(i1, i2, data);
		valid->is_transition = false;
	}
	else if (condition_traverse_the_array(2, i1, i2, data))
	{
		put_char_and_join(i1, i2, data);
		valid->is_quota = true;
		valid->is_transition = false;
	}
	else if (data->btree->content[i1][i2] == '\"' && valid->is_quota)
	{
		put_char_and_join(i1, i2, data);
		valid->is_quota = false;
		valid->is_transition = false;
	}
	else if (condition_traverse_the_array(3, i1, i2, data))
		i2 = put_environment(i1, i2, valid, data);
	return (i2);
}

int	trasition_master_master(int i1, int i2, t_valid	*valid, t_data *data)
{
	if (valid->is_transition)
	{
		while (data->btree->content[i1][i2]
			&& data->btree->content[i1][i2] != ' ')
		{
			if (data->btree->content[i1][i2] == '\'')
			{
				ft_putchar_fd(data->btree->content[i1][i2], 1);
				i2++;
			}
			i2++;
		}
	}
	else
		i2++;
	return (i2);
}
