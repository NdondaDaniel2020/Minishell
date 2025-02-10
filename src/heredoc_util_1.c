/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_heredoc_redirection_util(int i, t_new_list *aux, int len,
	int *n)
{
	int		pos;
	char	*tmp;

	pos = 0;
	tmp = ft_strnstr(aux->content[i], "<<", len);
	while (ft_strnstr((tmp + pos), "<<", len))
	{
		(*n)++;
		pos += 2;
	}
}

int	count_heredoc_redirection(t_data *data)
{
	int			n;
	int			i;
	int			len;
	t_new_list	*aux;

	n = 0;
	len = 0;
	aux = data->list;
	while (aux)
	{
		i = 0;
		while (aux->content[i])
		{
			len = ft_strlen(aux->content[i]);
			if (ft_strnpos2(aux->content[i], "<<", len) != -1
				&& ft_strncmp(aux->content[i], "<<", 2) == 0)
				n++;
			else if (ft_strnpos2(aux->content[i], "<<", len) != -1)
				count_heredoc_redirection_util(i, aux, len, &n);
			i++;
		}
		aux = aux->next;
	}
	return (n);
}

static void	first_enter_heredoc(int len, int *pos, char **new_content,
	t_data *data)
{
	int	i;

	i = 0;
	while (new_content[i])
	{
		if (ft_strncmp(new_content[i], "<<", 2) == 0)
		{
			(*pos)++;
			heredoc(data, new_content[i + 1]);
			if ((*pos) != len)
				close(data->read_in_the_pipe);
		}
		i++;
	}
	free_matrix(new_content);
}

static void	second_enter_heredoc(int len, int *pos, t_new_list *aux,
	t_data *data)
{
	int	i;

	i = 0;
	while (aux->content[i])
	{
		if (ft_strncmp(aux->content[i], "<<", 2) == 0)
		{
			(*pos)++;
			heredoc(data, aux->content[i + 1]);
			if ((*pos) != len)
				close(data->read_in_the_pipe);
		}
		i++;
	}
}

void	get_name_for_heredoc_redirection(t_data *data)
{
	int			pos;
	int			len;
	t_new_list	*aux;
	char		**new_content;

	pos = 0;
	aux = data->list;
	len = count_heredoc_redirection(data);
	while (aux)
	{
		new_content = reset_the_array_for_redirection(aux->content);
		if (new_content != NULL)
			first_enter_heredoc(len, &pos, new_content, data);
		else
			second_enter_heredoc(len, &pos, aux, data);
		aux = aux->next;
	}
}
