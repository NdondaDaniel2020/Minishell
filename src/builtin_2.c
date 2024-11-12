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
/*
static void	get_env_variable(int *i1, int *i2, t_data *data)
{
	int		c;
	char	*env_var;

	c = 1;
	while (data->split_cmd[*i1][*i2 + c] && data->split_cmd[*i1][*i2 + c] != ' ')
		c++;
	env_var = ft_calloc(c + 1, sizeof(char));
	c = 0;
	(*i2)++;
	while (data->split_cmd[*i1][*i2] && data->split_cmd[*i1][*i2] != ' ')
	{
		env_var[c] = data->split_cmd[*i1][*i2];
		(*i2)++;
		c++;
	}
	data->put_amb = getenv(env_var);
	if (data->put_amb)
	{
		data->output = ft_strjoin_free(data->output, data->put_amb);
		ft_printf("%s", data->put_amb);
	}
	else
	{
		data->output = ft_strjoin_free(data->output, "\n");
		ft_printf("\n");
	}
}

static void	scroll_word(int i1, t_data *data)
{
	int	i2;

	i2 = 0;
	while (data->split_cmd[i1][i2])
	{
		if (data->split_cmd[i1][i2] != '$' && data->split_cmd[i1][i2] != '"' &&
			data->split_cmd[i1][i2] != '\'')
		{
			data->output = ft_charjoin_free(data->output, data->split_cmd[i1][i2]);
			ft_putchar_fd(data->split_cmd[i1][i2], 1);
		}
		else if (data->split_cmd[i1][i2] == '$')
			get_env_variable(&i1, &i2, data);
		i2++;
	}
	if (data->split_cmd[i1 + 1])
		ft_putchar_fd(' ', 1);
}

void	echo(t_data *data)
{
	int	i1;

	i1 = 0;
	data->output = ft_calloc(1, sizeof(char));
	while (data->split_cmd[i1])
		i1++;
	if (i1 == 1)
	{
		data->output = ft_charjoin_free(data->output, '\n');
		ft_putchar_fd('\n', 1);
		return ;
	}
	i1 = 1;
	while (ft_strnstr(data->split_cmd[i1], "-n", ft_strlen(data->split_cmd[i1])))
		i1++;
	while (data->split_cmd[i1])
	{
		scroll_word(i1, data);
		i1++;
	}
	if (ft_strncmp(data->split_cmd[1], "-n", ft_strlen(data->split_cmd[1])))
	{
		data->output = ft_charjoin_free(data->output, '\n');
		ft_putchar_fd('\n', 1);
	}
}
*/
/*data->btree->content[i]*/