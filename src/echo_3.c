/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*allocate_memory_to_env(int i1, int i2, t_data *data)
{
	int		c;
	int		i;
	char	*env_var;

	i = 0;
	c = 0;
	while (data->btree->content[i1][i2 + c] &&
		!ft_isalpha(data->btree->content[i1][i2 + c]))
	{
		if (data->btree->content[i1][i2 + c] == '\'')
			i++;
		c++;
	}
	while (data->btree->content[i1][i2 + c] &&
		(data->btree->content[i1][i2 + c] != ' ' &&
		data->btree->content[i1][i2 + c] != '\"'))
	{
		i++;
		c++;
	}
	env_var = ft_calloc(i + 1, sizeof(char));
	return (env_var);
}

static int	put_single_quote(int i1, int i2, t_data *data)
{
	if (ft_strchr(data->btree->content[i1], '\''))
	{
		while (i2 > 0 && data->btree->content[i1][i2])
		{
			if (data->btree->content[i1][i2] == '\'')
			{
				ft_putchar_fd(data->btree->content[i1][i2], 1);
				data->output = ft_charjoin_free(data->output,
						data->btree->content[i1][i2]);
				i2++;
				break ;
			}
			i2++;
		}
	}
	return (i2);
}

static void	put_env(int i1, char *env_var, t_data *data)
{
	if (data->put_amb)
	{
		data->output = ft_strjoin_free(data->output, data->put_amb);
		ft_printf("%s", data->put_amb);
		data->space = true;
	}
	else if (data->put_amb == NULL && data->btree->content[i1 + 1] == NULL)
	{
		data->output = ft_strjoin_free(data->output, "\n");
		ft_printf("\n");
		data->space = true;
	}
	else
		data->space = false;
	if (env_var)
		free(env_var);
}

int	put_environment(int i1, int i2, t_valid	*valid, t_data *data)
{
	int		c;
	int		i;
	char	*env_var;

	c = 0;
	i = 0;
	env_var = allocate_memory_to_env(i1, i2, data);
	while (data->btree->content[i1][i2 + i] &&
		(data->btree->content[i1][i2 + i] != ' ' &&
		data->btree->content[i1][i2 + i] != '\"'))
	{
		if (ft_isalpha(data->btree->content[i1][i2 + i]))
		{
			env_var[c] = data->btree->content[i1][i2 + i];
			c++;
		}
		i++;
	}
	i2 = put_single_quote(i1, i2, data);
	data->put_amb = getenv(env_var);
	put_env(i1, env_var, data);
	if (i2 >= 0)
		valid->is_transition = true;
	data->space = true;
	return (i2);
}