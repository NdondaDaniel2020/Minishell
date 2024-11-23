/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		i++;
	return (i);
}

void	init_valid(t_valid	*valid)
{
	valid->is_quota = false;
	valid->is_transition = false;
}

static bool	echo_is_empty(int i, t_data *data)
{
	if (i == 1)
	{
		data->output = ft_calloc(1, sizeof(char));
		data->output = ft_charjoin_free(data->output, '\n');
		ft_putchar_fd('\n', 1);
		return (1);
	}
	return (0);
}

static void	add_bar_n(int i, t_data *data)
{
	if (ft_strncmp(data->btree->content[i - 1], "-n",
			ft_strlen(data->btree->content[i - 1])))
	{
		data->output = ft_charjoin_free(data->output, '\n');
		ft_putchar_fd('\n', 1);
	}
	if (data->output[0] == '\0')
		free(data->output);
}

void	echo(t_data *data)
{
	int		i1;
	int		i2;
	t_valid	valid;

	init_valid(&valid);
	i1 = count_word(data->btree->content);
	if (echo_is_empty(i1, data))
		return ;
	i1 = 0;
	while (!ft_strncmp(data->btree->content[i1], "echo", ft_strlen(data->btree->content[i1])))
		i1++;
	traverse_n(&i1, data);
	data->output = ft_calloc(1, sizeof(char));
	while (data->btree->content[i1])
	{
		i2 = 0;
		while (data->btree->content[i1][i2])
		{
			i2 = traverse_the_array(i1, i2, &valid, data);
			i2 = trasition_master_master(i1, i2, &valid, data);
		}
		if (data->btree->content[i1 + 1] && data->space)
			ft_putchar_fd(' ', 1);
		i1++;
	}
	add_bar_n(i1, data);
}
