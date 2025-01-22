/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_charjoin(char *s1, char c)
{
	char	*join;
	int		l1;
	int		i;

	if (!s1 && !c)
		return (NULL);
	i = 0;
	l1 = ft_strlen(s1);
	join = malloc((l1 + 2) * sizeof(char));
	if (!join)
		return (NULL);
	while (i < (l1 + 1))
	{
		if (i < l1)
			join[i] = s1[i];
		else
			join[i] = c;
		i++;
	}
	join[i] = '\0';
	return (join);
}

char	*ft_charjoin_free(char *s1, char c)
{
	char	*join;
	int		l1;
	int		i;

	if (!s1 && !c)
		return (NULL);
	i = 0;
	l1 = ft_strlen(s1);
	join = malloc((l1 + 2) * sizeof(char));
	if (!join)
		return (NULL);
	while (i < (l1 + 1))
	{
		if (i < l1)
			join[i] = s1[i];
		else
			join[i] = c;
		i++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
}

void	init_data(t_data *data)
{
	data->path = NULL;
	data->list = NULL;
	data->space = false;
	data->output = NULL;
	data->command = NULL;
	data->put_amb = NULL;
	data->is_pipe = false;
	data->automatic_input = false;
	data->read_in_the_pipe = -1;
	data->write_on_the_pipe = -1;
	data->write_pipe_operation = -1;
	data->read_pipe_operation = -1;
	data->cpy_read_pipe_operation = -1;
	data->cpy_write_operation = -1;
	data->cpy_read_operation = -1;
	data->redirection_matrix = NULL;
	data->heredoc_line_delimited = 2;
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	free_all_data(t_data *data)
{
	if (!data)
		return ;
	if (data->command)
	{
		free(data->command);
		data->command = NULL;
	}
	if (data->list)
	{
		while (data->list)
			ft_lstnew_delback(&data->list);
		data->list = NULL;
	}
}
