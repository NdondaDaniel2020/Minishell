/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
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

bool	echo_is_empty(int i, t_data *data)
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

void	traverse_n(int *i, t_data *data)
{
	while (data->btree->content[*i] &&
			ft_strnstr(data->btree->content[*i],
			"-n", ft_strlen(data->btree->content[*i])))
		(*i)++;
}

void	add_bar_n(int i, t_data *data)
{
	if (ft_strncmp(data->btree->content[i - 1], "-n", ft_strlen(data->btree->content[i - 1])))
	{
		data->output = ft_charjoin_free(data->output, '\n');
		ft_putchar_fd('\n', 1);
	}
	if (data->output[0] == '\0')
		free(data->output);
}

void	echo(t_data *data)
{
	int	i1;

	i1 = count_word(data->btree->content);
	if (echo_is_empty(i1, data))
		return ;
	i1 = 1;
	traverse_n(&i1, data);

	ft_printf("%i - %s\n", i1, data->btree->content[i1]);

}
