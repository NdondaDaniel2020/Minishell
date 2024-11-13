/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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
	data->btree = NULL;
	data->space = false;
	data->output = NULL;
	data->command = NULL;
	data->put_amb = NULL;
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
    if (data->output)
	{
		if (!ft_strnstr(data->command, data->output, ft_strlen(data->command)))
		{
			free(data->output);
			data->output = NULL;
		}
		// free(data->output);
		// data->output = NULL;
	}
    if (data->put_amb)
	{
		free(data->put_amb);
		data->put_amb = NULL;
	}
    if (data->btree)
        remove_all_tree(data->btree);
}
