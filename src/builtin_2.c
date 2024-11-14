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
	if (ft_strncmp(data->btree->content[i - 1], "-n",
		ft_strlen(data->btree->content[i - 1])))
	{
		data->output = ft_charjoin_free(data->output, '\n');
		ft_putchar_fd('\n', 1);
	}
	if (data->output[0] == '\0')
		free(data->output);
}

char	*allocate_memory_to_env(int i1, int *i2, t_data *data)
{
	int		c;
	int		i;
	char	*env_var;

	i = 0;
	c = 0;
	while (data->btree->content[i1][*i2 + c] &&
		!ft_isalpha(data->btree->content[i1][*i2 + c]))
	{
		if (data->btree->content[i1][*i2 + c] == '\'')
			i++;
		c++;
	}
	while (data->btree->content[i1][*i2 + c] && 
		(data->btree->content[i1][*i2 + c] != ' ' &&
		data->btree->content[i1][*i2 + c] != '\"'))
	{
		i++;
		c++;
	}
	env_var = ft_calloc(i + 1, sizeof(char));
	return (env_var);
}

void	put_single_quote(int i1, int *i2, t_data *data)
{
	if (ft_strchr(data->btree->content[i1], '\''))
	{
		while (*i2 > 0 && data->btree->content[i1][*i2])
		{
			if (data->btree->content[i1][*i2] == '\'')
			{
				ft_putchar_fd(data->btree->content[i1][*i2], 1);
				data->output = ft_charjoin_free(data->output,
					data->btree->content[i1][*i2]);
				(*i2)++;
				break;
			}
			(*i2)++;
		}
	}
}

void	put_env(int i1, char *env_var, t_data *data)
{		
	if (data->put_amb)
	{
		data->output = ft_strjoin_free(data->output, data->put_amb);
		ft_printf("%s", data->put_amb);
		data->space = true;
	}
	else if (data->put_amb == NULL &&
			data->btree->content[i1 + 1] == NULL)
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

void	put_environment(int i1, int *i2, t_data *data)
{
	int		c;
	int		i;
	char	*env_var;

	c = 0;
	i = 0;
	env_var = allocate_memory_to_env(i1, i2, data);
	while (data->btree->content[i1][*i2 + i] && 
		(data->btree->content[i1][*i2 + i] != ' ' &&
		data->btree->content[i1][*i2 + i] != '\"'))
	{
		if (ft_isalpha(data->btree->content[i1][*i2 + i]))
		{
			env_var[c] = data->btree->content[i1][*i2 + i];
			c++;
		}
		i++;
	}
	put_single_quote(i1, i2, data);
	data->put_amb = getenv(env_var);
	put_env(i1, env_var, data);
	// put_single_quote(i1, i2, data);
	while (*i2 > 0 && data->btree->content[i1][*i2])  //  o erro esta aqui
	{
		if (data->btree->content[i1][*i2] == '\'')
		{
			ft_putchar_fd(data->btree->content[i1][*i2], 1);
			data->output = ft_charjoin_free(data->output,
				data->btree->content[i1][*i2]);
			(*i2)++;
			break;
		}
		(*i2)++;
	}
	data->space = true;
}

void	traverse_the_array(int i1, int *i2, bool *quota, t_data *data)
{
	if (data->btree->content[i1][*i2] != '$' && data->btree->content[i1][*i2] != '"' && data->btree->content[i1][*i2] != '\'')
	{
		data->output = ft_charjoin_free(data->output, data->btree->content[i1][*i2]);
		ft_putchar_fd(data->btree->content[i1][*i2], 1);
		data->space = true;
	}
	else if ((data->btree->content[i1][*i2] == '\"' && data->btree->content[i1][*i2 + 1] == '$') || (data->btree->content[i1][*i2] == '$' && *i2 > 0 && data->btree->content[i1][*i2 - 1] == '\"'))
	{
		data->output = ft_charjoin_free(data->output,
			data->btree->content[i1][*i2]);
		ft_putchar_fd(data->btree->content[i1][*i2], 1);
		data->space = true;
		*quota = true;
	}
	else if (data->btree->content[i1][*i2] == '\"' && *quota)
	{
		data->output = ft_charjoin_free(data->output,
			data->btree->content[i1][*i2]);
		ft_putchar_fd(data->btree->content[i1][*i2], 1);
		data->space = true;
		*quota = false;
	}
	else if (data->btree->content[i1][*i2] == '$' || (data->btree->content[i1][*i2] == '\'' && data->btree->content[i1][*i2 + 1] == '$'))
		put_environment(i1, i2, data);
}

void	echo(t_data *data)
{
	int		i1;
	int		i2;
	bool	quota;

	i1 = count_word(data->btree->content);
	if (echo_is_empty(i1, data))
		return ;
	i1 = 1;
	quota = false;
	traverse_n(&i1, data);
	data->output = ft_calloc(1, sizeof(char));
	while (data->btree->content[i1])
	{
		i2 = 0;
		while (data->btree->content[i1][i2])
		{
			traverse_the_array(i1, &i2, &quota, data);
			i2++;
		}
		if (data->btree->content[i1 + 1] && data->space)
			ft_putchar_fd(' ', 1);
		i1++;
	}
	add_bar_n(i1, data);
}

/*
echo '"$HOME"'  ->  "$HOME"
echo "'$HOME'"  ->  '/home/kali'
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
scroll argument
while (data->btree->content[i1])
{
	i2 = 0;
	while (data->btree->content[i1][i2])
	{
		if (data->btree->content[i1][i2] != '$' && data->btree->content[i1][i2] != '"' && data->btree->content[i1][i2] != '\'')
		{
			data->output = ft_charjoin_free(data->output, data->btree->content[i1][i2]);
			ft_putchar_fd(data->btree->content[i1][i2], 1);
			data->space = true;
		}
		else if (data->btree->content[i1][i2] == '$')
		{
			get env
		}
		i2++;
	}
	if (data->btree->content[i1 + 1] && data->space)
		ft_putchar_fd(' ', 1);

	i1++;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
get env
c = 1;
while (data->btree->content[i1][i2 + c] && data->btree->content[i1][i2 + c] != ' ')
	c++;
env_var = ft_calloc(c + 1, sizeof(char));
c = 0;
(i2)++;
while (data->btree->content[i1][i2] && data->btree->content[i1][i2] != ' ')
{
	env_var[c] = data->btree->content[i1][i2];
	(i2)++;
	c++;
}
data->put_amb = getenv(env_var);
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
if (data->put_amb)
	free(env_var);





*/